/**********************************************************
*          SEGGER MICROCONTROLLER SYSTEME GmbH
*   Solutions for real time microcontroller applications
***********************************************************
File    : HIF_UART.c
Purpose : Terminal control for Flasher using UART.
--------- END-OF-HEADER ---------------------------------*/

#include "SEGGER_SYSVIEW.h"

#if (SEGGER_UART_REC == 1)

#include "NuMicro.h"
#include "SEGGER_RTT.h"
#include "system.h"

#define OS_FSYS PLL_CLOCK  // MCU core frequency
// ...

typedef void UART_ON_RX_FUNC(uint8_t Data);
typedef int UART_ON_TX_FUNC(uint8_t *pChar);

typedef UART_ON_TX_FUNC *UART_ON_TX_FUNC_P;
typedef UART_ON_RX_FUNC *UART_ON_RX_FUNC_P;

static UART_ON_RX_FUNC_P _cbOnRx;
static UART_ON_TX_FUNC_P _cbOnTx;

void HIF_UART_Init(uint32_t Baudrate,
                   UART_ON_TX_FUNC_P cbOnTx,
                   UART_ON_RX_FUNC_P cbOnRx);

#define _SERVER_HELLO_SIZE (4)
#define _TARGET_HELLO_SIZE (4)

// "Hello" message expected by SysView:
//  [ 'S', 'V', <PROTOCOL_MAJOR>, <PROTOCOL_MINOR> ]
static const U8 _abHelloMsg[_TARGET_HELLO_SIZE] = {
    'S', 'V', (SEGGER_SYSVIEW_VERSION / 10000),
    (SEGGER_SYSVIEW_VERSION / 1000) % 10};

static struct {
    U8 NumBytesHelloRcvd;
    U8 NumBytesHelloSent;
    int ChannelID;
} _SVInfo = {0, 0, 1};

static void _StartSysView(void)
{
    int res;

    res = SEGGER_SYSVIEW_IsStarted();
    if (res == 0) {
        SEGGER_SYSVIEW_Start();
    }
}

static void _cbOnUARTRx(U8 Data)
{
    // Not all bytes of <Hello> message received by SysView yet?
    if (_SVInfo.NumBytesHelloRcvd < _SERVER_HELLO_SIZE) {
        _SVInfo.NumBytesHelloRcvd++;
        goto Done;
    }
    _StartSysView();

    // Write data into corresponding RTT buffer for application to read
    // and handle accordingly
    SEGGER_RTT_WriteDownBuffer(_SVInfo.ChannelID, &Data, 1);
Done:
    return;
}

static int _cbOnUARTTx(U8 *pChar)
{
    int r;

    // Not all bytes of <Hello> message sent to SysView yet?
    if (_SVInfo.NumBytesHelloSent < _TARGET_HELLO_SIZE) {
        *pChar = _abHelloMsg[_SVInfo.NumBytesHelloSent];
        _SVInfo.NumBytesHelloSent++;
        r = 1;
        goto Done;
    }
    r = SEGGER_RTT_ReadUpBufferNoLock(_SVInfo.ChannelID, pChar, 1);
    if (r < 0) {  // Failed to read from up buffer?
        r = 0;
    }
Done:
    return r;
}

void SEGGER_UART_init(U32 baud)
{
    HIF_UART_Init(baud, _cbOnUARTTx, _cbOnUARTRx);
}

/**
 * @brief HIF_UART_WaitForTxEnd
 */
void HIF_UART_WaitForTxEnd(void)
{
    // Wait specified UART port transmission is over
    UART_WAIT_TX_EMPTY(UART0);
}

/**
 * @brief UART0_IRQHandler
 *    Interrupt handler. Handles both, Rx and Tx interrupts
 *
 *  Notes
 *    (1) This is a high-prio interrupt so it may NOT use embOS functions
 *        However, this also means that embOS will never disable this interrupt
 */
void UART0_IRQHandler(void)
{
    // TODO:
}

/**
 * @brief HIF_UART_EnableTXEInterrupt
 */
void HIF_UART_EnableTXEInterrupt(void)
{
    // Transmitter Empty Interrupt Enable
    UART0->INTEN |= UART_INTEN_TXENDIEN_Msk;
}

/**
 * @brief HIF_UART_Init()
 *
 * @param Baudrate UART baudrate
 * @param cbOnTx TX callback function
 * @param cbOnRx RX callback function
 */
void HIF_UART_Init(uint32_t Baudrate,
                   UART_ON_TX_FUNC_P cbOnTx,
                   UART_ON_RX_FUNC_P cbOnRx)
{
    /***************************************************************************
     * Clock setting
     **************************************************************************/
    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART clock source from HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT,
                       CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and
     * CyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /***************************************************************************
     * Configure USART RX/TX pins for alternate function usage
     **************************************************************************/
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |=
        (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /***************************************************************************
     * Init UART to Baudrate-8n1 for segger systemview
     **************************************************************************/
    uint32_t u32ClkTbl[4] = {__HXT, 0ul, __LXT, __HIRC};

    /* Get UART clock source selection */
    uint32_t u32UartClkSrcSel =
        ((uint32_t) (CLK->CLKSEL1 & CLK_CLKSEL1_UART0SEL_Msk)) >>
        CLK_CLKSEL1_UART0SEL_Pos;
    /* Get UART clock divider number */
    uint32_t u32UartClkDivNum =
        (CLK->CLKDIV0 & CLK_CLKDIV0_UART0DIV_Msk) >> CLK_CLKDIV0_UART0DIV_Pos;

    /* Select UART function */
    UART0->FUNCSEL = UART_FUNCSEL_UART;

    /* Set UART line configuration */
    UART0->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;

    /* Set UART Rx and RTS trigger level */
    UART0->FIFO &= ~(UART_FIFO_RFITL_Msk | UART_FIFO_RTSTRGLV_Msk);

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u32UartClkSrcSel == 1ul) {
        u32ClkTbl[u32UartClkSrcSel] = CLK_GetPLLClockFreq();
    }

    /* Set UART baud rate */
    if (Baudrate != 0ul) {
        uint32_t u32Baud_Div = UART_BAUD_MODE2_DIVIDER(
            (u32ClkTbl[u32UartClkSrcSel]) / (u32UartClkDivNum + 1ul), Baudrate);

        if (u32Baud_Div > 0xFFFFul) {
            UART0->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(
                                                 (u32ClkTbl[u32UartClkSrcSel]) /
                                                     (u32UartClkDivNum + 1ul),
                                                 Baudrate));
        } else {
            UART0->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
        }
    }

    /***************************************************************************
     * Setup callbacks which are called by ISR handler
     * and enable interrupt in NVIC
     **************************************************************************/
    _cbOnRx = cbOnRx;
    _cbOnTx = cbOnTx;

    // Highest prio, so it is not disabled by embOS
    NVIC_SetPriority(UART1_IRQn, 6);
    NVIC_EnableIRQ(UART1_IRQn);
}

#endif
