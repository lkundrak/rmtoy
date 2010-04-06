/* Universal */
#define CR	0x00 /* Command */
# define STP	0x01 /* Stop */
# define STA	0x02 /* Start */
# define TXP	0x04 /* Transmit packet */
# define RD0	0x08 /* Remote DMA command 0 */
# define RD1	0x10 /* Remote DMA command 1 */
# define RD2	0x20 /* Remote DMA command 2 */
#  define READ	RD0  /* Remote read */
#  define WRITE	RD1  /* Remote write */
#  define SEND	(RD0 | RD1) /* Send packet */
#  define ABORT	RD2  /* Abort/Complete remote DMA */
# define PS0	0x40 /* Page select 0 */
# define PS1	0x80 /* Page select 1 */
#  define PAGE0	0    /* Page 0 */
#  define PAGE1	PS0  /* Page 1 */
#  define PAGE2	PS1  /* Page 2 */

/* Read page 0 */
#define CLDA0	0x01 /* Current Local DMA Address 0 */
#define CLDA1	0x02 /* Current Local DMA Address 1 */
#define BNRY	0x03 /* Boundary Pointer */
#define TSR	0x04 /* Transmit Status Register */
# define PTX    0x01 /* Packet Transmitted */
# define COL    0x04 /* Transmit Collided */
# define ABT    0x08 /* Transmit Aborted */
# define CRS    0x10 /* Carrier Sense Lost */
# define FU     0x20 /* FIFO Underrun */
# define CDH    0x40 /* CD Heartbeat */
# define OWC    0x80 /* Out Of Window Collision */
#define NCR	0x05 /* Number of Collisions Register */
#define FIFO	0x06 /* FIFO */
# define WTS    0x01 /* Word Transfer Select */
# define BOS    0x02 /* Byte Order Select */
# define LAS    0x04 /* Long Address Select */
# define LS     0x08 /* Loopback Select */
# define AR     0x10 /* Auto-Initialize Remote */
# define FT0    0x20 /* FIFO Threshhold Select Encoded 0 */
# define FT1    0x40 /* FIFO Threshhold Select Encoded 1 */
#  define B2    0    /* 1 Word, 2 Bytes */
#  define B4    FT0  /* 2 Words, 4 Bytes */
#  define B8    FT1  /* 4 Words, 8 Bytes */
#  define BC    (FT0 | FT1) /* 6 Words, 12 Bytes */
#define ISR	0x07 /* Interrupt Status Register */
# define PRX    0x01 /* Packet Received */
# define PTX    0x02 /* Packet Transmitted */
# define RXE    0x04 /* Receive Error */
# define TXE    0x08 /* Transmit Error */
# define OVW    0x10 /* Overwrite Warning */
# define CNT    0x20 /* Counter Overflow */
# define RDC    0x40 /* Remote DMA Complete */
# define RST    0x80 /* Reset Status */
#define CRDA0	0x08 /* Current Remote DMA Address 0 */
#define CRDA1	0x09 /* Current Remote DMA Address 1 */
#define RSR	0x0c /* Receive Status Register */
# define PRX    0x01 /* Packet Received Intact */
# define CRC    0x02 /* CRC Error */
# define FAE    0x04 /* Frame Alignment Error */
# define FO     0x08 /* FIFO Overrun */
# define MPA    0x10 /* Missed Packet */
# define PHY    0x20 /* Physical Multicast Address */
# define DIS    0x40 /* Receiver Disabled */
# define DFR    0x80 /* Deferring */
#define CNTR0	0x0d /* Tally Counter 0 (Frame Alignment Errors) */
#define CNTR1	0x0e /* Tally Counter 1 (CRC Errors) */
#define CNTR2	0x0f /* Tally Counter 2 (Missed Packet Errors) */

/* Write page 0 */
#define PSTART	0x01 /* Page Start Register */
#define PSTOP	0x02 /* Page Stop Register */
#define BNRY	0x03 /* Boundary Pointer */
#define TPSR	0x04 /* Transmit Page Start Address */
#define TBCR0	0x05 /* Transmit Byte Count Register 0 */
#define TBCR1	0x06 /* Transmit Byte Count Register 1 */
#define ISR	0x07 /* Interrupt Status Register */
# define PRXE   0x01 /* Packet Received Interrupt Enable */
# define PTXE   0x02 /* Packet Transmitted Interrupt Enable */
# define RXEE   0x04 /* Receive Error Interrupt Enable */
# define TXEE   0x08 /* Transmit Error Interrupt Enable */
# define OVWE   0x10 /* Overwrite Warning Interrupt Enable */
# define CNTE   0x20 /* Counter Overflow Interrupt Enable */
# define RDCE   0x40 /* DMA Complete Interrupt Enable */
#define RSAR0	0x08 /* Remote Start Address Register 0 */
#define RSAR1	0x09 /* Remote Start Address Register 1 */
#define RBCR0	0x0a /* Remote Byte Count Register 0 */
#define RBCR1	0x0b /* Remote Byte Count Register 1 */
#define RCR	0x0c /* Receive Configuration Register */
# define SEP    0x01 /* Save Errored Packets */
# define AR     0x02 /* Accept Runt Packets */
# define AB     0x04 /* Accept Broadcast */
# define AM     0x08 /* Accept Multicast */
# define PRO    0x10 /* Promiscuous Physical */
# define MON    0x20 /* Monitor Mode */
#define TCR	0x0d /* Transmit Configuration Register */
# define CRC    0x01 /* Inhibit CRC */
# define LB0    0x02 /* Encoded Loopback Control 0 */
# define LB1    0x04 /* Encoded Loopback Control 1 */
#  define MODE0 0    /* Normal Operation (LPBK = 0) */
#  define MODE1 LB0  /* Internal Loopback (LPBK = 0) */
#  define MODE2 LB1  /* External Loopback (LPBK = 1) */
#  define MODE3 (LB0 | LB1) /* External Loopback (LPBK = 0) */
# define ATD    0x08 /* Auto Transmit Disable */
# define OFST   0x10 /* Collision Offset Enable */
#define DCR	0x0e /* Data Configuration Register */
# define WTS    0x01 /* Word Transfer Select */
# define BOS    0x02 /* Byte Order Select */
# define LAS    0x04 /* Long Address Select */
# define LS     0x08 /* Loopback Select */
# define AR     0x10 /* Auto-Initialize Remote */
# define FT0    0x20 /* FIFO Threshold Select Encoded 0 */
# define FT1    0x40 /* FIFO Threshold Select Encoded 1 */
#  define B2    0    /* 1 Word, 2 Bytes */
#  define B4    FT0  /* 2 Words, 4 Bytes */
#  define B8    FT1  /* 4 Words, 8 Bytes */
#  define BC    (FT0 | FT1) /* 6 Words, 12 Bytes */
#define IMR	0x0f /* Interrupt Mask Register */
# define PRXE   0x01 /* Packet Received Interrupt Enable */
# define PTXE   0x02 /* Packet Transmitted Interrupt Enable */
# define RXEE   0x04 /* Receive Error Interrupt Enable */
# define TXEE   0x08 /* Transmit Error Interrupt Enable */
# define OVWE   0x10 /* Overwrite Warning Interrupt Enable */
# define CNTE   0x20 /* Counter Overflow Interrupt Enable */
# define RDCE   0x40 /* DMA Complete Interrupt Enable */

/* Read/write page 1 */
#define PAR0	0x01 /* Physical Address Register 0 */
#define CURR	0x07 /* Current Page Register */
#define MAR0	0x08 /* Multicast Address Register 0 */
