# **EMBEDDED IN AUTOMOTIVE**

## **CONTENTS**

[LESSON 1: GENERAL PURPOSE INPUT OUTPUT](#Lesson1)

[LESSON 2: INTERRUPT & TIMER](#Lesson2)

[LESSON 3: BASIC COMMUNICATION STANDARDS](#Lesson3)

[LESSON 4: DIRECT MEMORY ACCESS (DMA)](#Lesson4)

[LESSON 5: ANALOG TO DIGITAL CONVERTER (ADC)](#Lesson5)

[LESSON 6: CONTROLLER AREA NETWORK (CAN)](#Lesson6)

----------------------------------------------------------
<a name="Lesson1"></a>
## **LESSON 1: GENERAL PURPOSE INPUT OUTPUT**
	
*Làm sao để cấu hình ngoại vi GPIO ?*

Để có thể cấu hình cho ngoại vi, chúng ta **luôn luôn** phải nhớ **cấp clock** trước tiên.

- B1: Cấp xung cho ngoại vi
	
	Dựa vào Reference Manual hoặc block diagram ta sử dụng hàm và cấp tham số cần thiết:
	
	RCC_(Tên Bus)PerighClockCmd(ngoại vi cần cấu hình, Trạng thái);
	
	Ví dụ: Chúng ta cần cấp xung cho thanh ghi GPIOC, ta thiết lập như sau:
	```c
	void RCC_Config() {
	  RCC_APB2PeriphClockCmd(RCC_APB2Phriph_GPIOC, ENABLE);
	}
	```
 
Sau khi ngoại vi được cấp clock, chúng ta có thể thiết lập các cấu hình cho ngoại vi đó.

- B2: Cấu hình ngoại vi

	Sau khi được cấp xung, ta sử dụng hàm GPIO_Init(GPIOx, &GPIO_InitStruct) để cấu hình
	
	Trong đó: 
	
	GPIOx           : GPIO cần cấu hình
	          
	GPIO_InitStruct : Biến chứa các thông tin để cấu hình cho GPIO có kiểu dữ liệu GPIO_InitTypeDef
	
	GPIO_InitTypeDef là 1 kiểu struct chứa các trường sau:
	
	          GPIO_Pin        : Chọn Pin đang cần để cấu hình
		  
	          GPIO_Mode       : Chọn chế độ cho Pin
		  
	          GPIO_Speed      : Chọn tốc độ phản hồi
	
	Nếu cấu hình Pin là đầu vào, ta có thể chọn:

	        Input Pull Down   : Thiết lập đầu vào và mức logic ở mức 0 (0V) khi không tác động
	        Input Pull Up     : Thiết lập đầu vào và mức logic ở mức 1 (3,3V) khi không tác động
		    Input Floating    : Thiết lập đầu vào và để nổi (ở giữa mức 0-3,3V)
  
	Nếu cấu hình Pin là đầu ra, ta thường sử dụng:

	        Output Push Pull  : Cho phép tùy chỉnh tín hiệu ở 2 mức logic 0 (0V) và 1 (3,3V)
		    Output Open Drain : Thiếp lập đấu ra có tín hiệu 0V và thả nổi 0-3,3V
	
	Ví dụ: Chúng ta cần cấu hình cho led PC13 và nút bấm PC15

	```c
	void GPIO_Config(void) {
		GPIO_InitTypeDef GPIO_InitStruct;
	 
		/* Config pin PC13 as Led's pin */
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			
		GPIO_Init(GPIOC, &GPIO_InitStruct);
			
		/* Config pin PC15 as Button's pin */
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_15;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			
		GPIO_Init(GPIOC, &GPIO_InitStruct); 
	}
	```
  
Sau khi thiết lập xong, ngoại vi đã có thể sử dụng, tùy thuộc vào mục đích, yêu cầu bài toán để sử dụng các Pin với các hàm tương ứng.

- B3: Sử dụng ngoại vi

	+ Đọc giá trị đầu vào tại 1 Pin (1 bit) của thanh ghi
	
	        uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	
	+ Đọc giá trị đầu vào của cả 1 thanh ghi
	
	        uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
	
	+ Đọc giá trị đầu ra tại 1 Pin (1 bit) của thanh ghi
	
	        uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	
	+ Đọc giá trị đầu ra của cả 1 thanh ghi
	
	        uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
	
	+ Thay đổi giá trị lên mức logic 1 của 1 Pin trên thanh ghi
	
	        void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	  
	+ Thay đổi giá trị về mức logic 0 của 1 Pin trên thanh ghi
	  
	        void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	
	+ Thay đổi giá trị của 1 Pin trên thanh ghi
	
	        void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
	
	+ Thay đổi giá trị của 1 Pin hoặc nhiều Pin trên thanh ghi
	
	        void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);

----------------------------------------------------------
<a name="Lesson2"></a>
## **LESSON 2: INTERRUPT & TIMER**	


----------------------------------------------------------
<a name="Lesson3"></a>
## **LESSON 3: BASIC COMMUNICATION STANDARDS**
*Các MCU trao đổi dữ liệu với nhau như thế nào ?*

Để có thể giao tiếp được 2 hoặc nhiều MCU với nhau, chúng ta cần có các giao thức để có thể liên lạc với nhau. Cũng giống việc chúng ta giao tiếp bằng ngôn ngữ, các MCU giao tiếp với nhau thông qua điện áp đi qua các chân đã được cấu hình. Ở phạm vi cơ bản này, chúng ta sẽ tìm hiểu về 3 chuẩn giao tiếp cơ bản và phổ biến là SPI, I2C và UART để nắm được cách hoạt động.

### 1. Serial peripheral interface (SPI)
*SPI là gì? Các chân tín hiệu ra sao ?*

- Là một chuẩn truyền thông nối tiếp đồng bộ
- Chế độ song công toàn phần, sử dụng mô hình Master-Slave. Trong đó Master sẽ khởi tạo frame cho việc gửi hoặc nhận.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/ed/SPI_single_slave.svg/1024px-SPI_single_slave.svg.png">

Bus SPI sử dụng 4 chân logic tín hiệu:
	SCLK (Serial Clock)       : Xung Clock phát ra từ Master
 	MOSI (Master Out Slave In): Dành cho việc truyền dữ liệu từ Master tới Slave
  	MISO (Master In Slave Out): Dành cho việc truyền dữ liệu từ Slave tới Master
   	CS/SS (Chip/Slave Select) : Chân CS được Master sử dụng để chọn Slave cần giao tiếp

*Vậy cách thức hoạt động SPI như thế nào ?*
<img src="https://deviot.vn/storage/deviot/Giao%20tiep%20SPI%207.png">

**Bước 1:** Chân SS nối với Slave tương ứng mà Master muốn truyền/nhận chuyển xuống mức logic thấp.

**Bước 2:** Cứ 1 xung clock, Master sẽ gửi đi 1 bit từ thanh ghi dịch (Shift Register) của nó đến thanh ghi dịch của Slave thông qua đường MOSI. Đồng thời Slave cũng gửi lại 1 bit đến cho Master qua đường MISO.Như vậy sau 8 chu kỳ clock thì hoàn tất việc truyền và nhận 1 byte dữ liệu.

**Bước 3:** Khi hoàn tất, Master sẽ ngừng việc cấp xung và chọn chân Slave tương ứng (khi đó chân SS được kéo lên mức logic cao).

*Có bao nhiêu chế độ hoạt động ?*

SPI Master cần cấu hình clock polarity (cực của xung) và clock phase.

<img src="https://deviot.vn/storage/deviot/Giao%20tiep%20SPI%203.png">

CPOL được xác định dựa trên xung SCK với
- CPOL = 0 tương ứng với việc xung nhịp đồng hồ ở mực thấp khi không làm việc.
- CPOL = 1 tương ứng với xung nhịp đồng hồ ở mức cao khi không làm việc.

CPHA được hiểu là vị trí lấy dữ liệu:
- CPHA = 0 tương ứng lấy dư liệu khi đang ở sườn lên
- CPHA = 1 tương ứng lấy dữ liệu khi đang ở sườn xuống

Từ các cách thiết lập của CPOL và CPHA mà chúng ta ra được 4 MODE:
| MODE | CPOL | CPHA |
|------|------|------|
| 0    | 0    | 0    |
| 1    | 0    | 1    |
| 2    | 1    | 0    |
| 3    | 1    | 1    |

*Có bao nhiêu cách để kết nối giao tiếp SPI*
- 1 thiết bị Master và 1 thiết bị Slave
<img src="https://deviot.vn/storage/deviot/Giao%20tiep%20SPI.png">
- 1 thiết bị Master và nhiều thiết bị Slave (chế độ độc lập) (*khá giống mắc song song*)
<img src="https://deviot.vn/storage/deviot/Giao%20tiep%20SPI%206.png">
- 1 thiết bị Master và nhiều thiết bị Slave (chế độ dây chuyền) (*khá giống mắc nối tiếp*)
<img src="https://deviot.vn/storage/deviot/Giao%20tiep%20SPI%208.png">

### 2. Inter-Integrated Circuit (I2C)

*I2C là gì? Cấu tạo của I2C như thế nào?*

- Là giao thức giao tiếp nối tiếp đồng bộ.
- Chế độ song công bán toàn phần.

I2C chỉ sử dụng 2 đường truyền tín hiệu:
- SCL - Serial Clock Line: Tạo xung clock do Master phát đi.
- SDA - Serial Data Line: Đường truyền nhận dữ liệu.

<img src="https://deviot.vn/storage/deviot/Giao%20ti%E1%BA%BFp%20I2C%202.png">

Hai bus SCL và SDA luôn được để ở trang thái cao, để khi các thiết bị được kết nối chỉ có thể kéo 2 đường dây này về mức thấp, không thể kéo lên mức cao. Tránh trường hợp 1 thiết bị kéo lên mức cao, 1 thiết bị kéo xuống mức thấp gây ngắn mạch.

*Data frame của I2C*

<img src="https://deviot.vn/storage/deviot/Giao%20ti%E1%BA%BFp%20I2C%203.png">

- Bit start: SDA chuyển từ mức cao xuống mức thấp trước khi đường SCL chuyển từ mức cao xuống mức thấp.
- Bit stop: SDA chuyển từ mức thấp sang sao sau khi SCL chuyển từ thấp lên cao.
- Khối bit địa chỉ: Do quá trình truyền nhận sẽ diễn ra với nhiều thiết bị, IC khác nhau nên chúng sẽ được gắn 1 địa chỉ vật lý cố định. (Từ 7-10 bit)
- Bit Read/Write: Bit này để xác định đây là quá trình truyền hay nhận dữ liệu từ thiết bị Master. '0' là truyền và '1' là nhận.
- Khối bit dữ liệu: Khung dữ liệu luôn có độ dài 8 bit, chứa dữ liệu được truyền đi hoặc nhận về.
- Bit ACK/NACK: sau khối địa chỉ và khối dữ liệu luôn có bit ACK/NACK để xác minh rằng dữ liệu đã được gửi thành công. Nếu trùng thì sẽ về mức thấp còn mặc định sẽ ở mức cao.

*Vậy I2C truyền nhận dữ liệu như thế nào?*

<img src="https://cdn.sparkfun.com/assets/learn_tutorials/8/2/I2C_Basic_Address_and_Data_Frames.jpg">

**Bước 1:** Master gửi bit bắt đầu đến các slave được kết nối bằng đường SDA từ mức cao xuống mức thấp trước khi SCL chuyển xuống mức thấp.

**Bước 2:** Master gửi cho mỗi Slave địa chỉ 7-10 bit của Slave mà Master muốn giao tiếp cùng với bit Read/Write.

**Bước 3:** Các Slave sẽ so sánh địa chỉ vừa nhận được với địa chỉ của chính nó. Nếu địa chỉ trùng khớp, Slave sẽ trả về bằng bit ACK/NACK bằng cách kéo SDA xuống thấp. Các Slave không sử dụng sẽ để mặc định SDA ở mức cao.

**Bước 4:** Master gửi hoặc nhận khối bit dữ liệu.

**Bước 5:** Sau khi khối bit dữ liệu, thiết bị nhận dữ liệu trả về 1 bit ACK/NACK khác để cho thiết bị gửi xác nhận đã chuyển xong khối bit dữ liệu.

**Bước 6:** Để dừng truyền dữ liệu, Master gửi điều kiện dừng đến Slave bằng cách chuyển SCL lên cao trước khi SDA chuyển lên mức cao.

Ghi nhớ: *SCL vào muộn ra sớm*

**Lưu ý:**
- Một Master có thể kết nối với nhiều Slave. Với 7 bit address sẽ có 128 (2^7) địa chỉ riêng biệt.
- Nhiều Master kết nối với một hoặc nhiều Slave. Khi nhận hay truyền dữ liệu cần đọc đường SDA thấp hoặc cao trước. Nếu SDA thấp có nghĩa đang có master khác đang thực thi, cần đợi SDA về mức cao để có thể truyền hoặc nhận dữ liệu.

### 3. Universal synchronous asynchronous receiver transmitter (USART)

*Khái niệm và cấu tạo về UART*

- Là bộ truyền nhận dữ liệu không đồng bộ.
- Hoạt động ở chế độ song công
- Gồm 2 đường truyền dữ liệu độc lập là TX (truyền) và RX (nhận).

<img src="https://vanhunteradams.com/Protocols/UART/uart_hardware.png">

Chân TX của thiết bị này được kết nối với trận RX của thiết bị còn lại.

Thông thường, tốc độ truyền của UART (baudrate) được đặt ở 1 số mốc chuẩn như 600, 1200, 9600, 19200 và một vài tốc độ khác. Các tốc độ này định nghĩa số lượng bit được truyền qua mỗi giây.

UART truyền dư liệu nối tiếp theo 3 chế độ
- Simplex: Chỉ tiến hành giao tiếp một chiều.
- Half duplex: Dữ liệu đi theo 1 hướng tại 1 thời điểm.
- Full duplex: Thực hiện giao tiếp đồng thời đến và đi.

*Vậy dữ liệu được truyền như thế nào?*

<img src='https://tapit.vn/wp-content/uploads/2018/06/1-2.png'>

Idle frame: Đường truyền UART luôn luôn ở mức "1".

Start bit: Bit đầu tiên gửi có chức năng thông báo cho bên nhận rằng sắp có một gói dữ liệu đang đến bằng cách kéo dòng truyền xuống mức "0".

Data: Thường là 5-9 bit. Trong quá trình truyền, bit có trọng số thấp được truyền trước.

Parity bit: Dùng để kiểm tra dữ liệu. Có 2 trạng thái là chẵn và lẻ. Tuy nhiên không thể tránh khỏi các tình huống lỗi data những kiểm tra vẫn ra kết quả đúng. Bit này không phải là bit bắt buộc nên có thể loại bỏ bit này ra khỏi khung truyền.

Stop bit: Là bit báo cho bộ truyền/nhận rằng dữ liệu đã được gửi xong. Stop bit có thể cấu hình là 1 bit, 1.5 bit, 2 bit, 0.5 bit.

Quá trình truyền dữ liệu UART sẽ bắt đầu bằng Start bit, đường mức cao được kéo dần xuống thấp. Sau Start bit là 5 – 9 bit data truyền trong khung dữ liệu của gói, theo sau là Parity bit (có thể không cần bit này) nhằm xác minh việc truyền dữ liệu thích hợp. Cuối cùng, Stop bit sẽ được truyền ở nơi đường đặt tại mức cao.

### 4. So sánh các phương thức giao tiếp

|       Đặc điểm      |                   SPI                   |                      I2C                      |                        UART                       |
|:-------------------:|:---------------------------------------:|:---------------------------------------------:|:-------------------------------------------------:|
| Kết nối             |                 Phức tạp                |                    Đơn giản                   |                      Đơn giản                     |
| Số dây kết nối      |                  4 dây                  |                     2 dây                     |                       2 dây                       |
| Chế độ truyền       |                Song công                |                   Song công                   |                   Bán song công                   |
| Tốc độ truyền       |       Đồng bộ (10Mbps đến 20Mbps)       |      Đồng bộ (100kbps, 400kbps, 3.4Mbps)      | Không đồng bộ (Tốc độ tự cài đặt, tối đa 460kbps) |
| Khoảng cách         |               Trên bo mạch              |                  Trên bo mạch                 |                  12m (lý thuyết)                  |
| Số thiết bị kết nối | Hạn chế (Giao tiếp bằng chọn chân chip) | 127 thiết bị (giao tiếp bằng chọn địa chỉ IC) |             2 thiết bị (Giao tiếp 1-1)            |

----------------------------------------------------------
<a name="Lesson4"></a>
## **LESSON 4: DIRECT MEMORY ACCESS (DMA)**

----------------------------------------------------------
<a name="Lesson5"></a>
## **LESSON 5: ANALOG TO DIGITAL CONVERTER (ADC)**
*ADC là gì? Định nghĩa về ADC?*
Vi điều khiển hay các thiết bị ngày nay đều sử dụng tín hiệu số dựa trên các bit nhị phân để hoạt động. Còn thực tế thì không chỉ mãi là tín hiệu số mà là tín hiệu tương tự và liên tục vì vậy cần phải có thiết bị chuyển đổi từ tín hiệu tương tự sang tín hiệu số.
*ADC - Analog to Digital Convert*: là 1 mạch điện tử lấy điện áp tương tự làm đầu vào và chuyển đổi nó thành dữ liệu số (1 giá trị đại diện cho mức điện áp trong mã nhị phân).
<img src = 'https://imgur.com/a/9PXW264'>
Khả năng chuyển đổi của ADC phụ thuộc vào 2 yếu tố:
- Độ phân giải: Số bit mà ADC sử dụng để mã hóa tín hiệu. Hay còn gọi là số mức tín hiệu được biểu diễn(có độ phân giải càng cao thì độ chính xác càng lớn).
- Tần số/Chu kì lấy mẫu: tốc độ/khoảng thời gian giữa 2 lần mã hóa(tần số lấy mẫu càng cao thì chuyển đổi sẽ có độ chính xác càng lớn).
 	- Tần số lấy mẫu = 1/(thời gian lấy mẫu + thời gian chuyển đổi).
  	- Tần số lấy mẫu phải lớn hơn tần số của tín hiệu ít nhất 2 lần để đảm bảo độ chính xác khi khôi phục lại tín hiệu.

*Vậy ADC ở trong STM32F1 được cấu hình như thế nào?*
Trong STM32 có 2 kênh ADC đó là ADC1 và ADC2, mỗi bộ có tối đa 9 channel với nhiều mode hoạt động, kết quả chuyển đổi được lưu trong thanh ghi 16 bit.
- Độ phân giải: 12 bit
- Có các ngắt hỗ trợ, có thể điều khiển hoạt động ADC bằng xung Trigger
- Thời gian chuyển đổi nhanh: 1us tại tần số 65MHz
- Có bộ DMA giúp tăng tốc độ xử lý

Sơ đồ khối bộ ADC
<img src= 'https://imgur.com/a/clOrXqe'>

 **Cấu hình ADC**
Các bộ ADC được cấp xung từ RCC APB2, để bộ ADC hoạt động cần cấp xung cho cả ADC để tạo tần số lấy mẫu tín hiệu và cấp xung cho GPIO của PORT ngõ vào.
 <img src = 'https://imgur.com/a/J8XR7fe'>

```
void RCC_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
```
ADC hỗ trợ rất nhiều kênh, mỗi kênh lấy tín hiệu từ các chân GPIO của các Port và từ các chân khác. Các chân GPIO dùng làm ngõ vào cho ADC sẽ được cấu hình Mode AIN.(Analogue Input).
<img src = 'https://imgur.com/a/uV2PeLH'>
```
void GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
```

**Các chế độ của ADC**
 Regular Conversion:
- Single: ADC chỉ đọc 1 kênh duy nhất, và chỉ đọc khi kênh nào được yêu cầu.
- Single Continous: sẽ đọc 1 kênh duy nhất, nhưng đọc dữ liệu nhiều lần.
- Scan: Multi-Channels: Quét qua và đọc dữ liệu nhiều kênh, nhưng chỉ đọc khi nào được yêu cầu.
- Scan: Continous Multi-Channels Repeat: Quét qua và đọc dữ liệu nhiều kênh, nhưng đọc liên tiếp nhiều lần giống như Single Continous.
Injected Conversion:
Trong trường hợp nhiều kênh hoạt động. Khi kênh có mức độ ưu tiên cao hơn có thể tạo ra một Injected Trigger. Khi gặp Injected Trigger thì ngay lập tức kênh đang hoạt động bị ngưng lại để kênh được ưu tiên kia có thể hoạt động.

**Các tham số của ADC**
- ADC_Mode:  Cấu hình chế độ hoạt động cho ADC là đơn (Independent) hay đa, ngoài ra còn có các chế độ ADC chuyển đổi tuần tự các kênh (regularly) hay chuyển đổi khi có kích hoạt (injected).
- ADC_NbrOfChannel: Số kênh ADC để cấu hình
- ADC_ContinuousConvMode: Cấu hình bộ ADC có chuyển đổi liên tục hay không, Enable để cấu hình ADC  chuyển đổi lien tục, nếu cấu hình Disable, ta phải gọi lại lệnh đọc ADC để bắt đầu quá trình chuyển đổi.
- ADC_ExternalTrigConv: Enable để sử dụng tín hiệu trigger.
- ADC_ScanConvMode: Cấu hình chế độ quét ADC lần lượt từng kênh. Enable nếu sử dụng chế độ quét này.
- ADC_DataAlign: Cấu hình căn lề cho data. Vì bộ ADC xuất ra giá trị 12bit, được lưu vào biến 16 hoặc 32 bit nên phải căn lề các bit về trái hoặc phải.

Ngoài các tham số trên, cần cấu hình thêm thời gian lấy mẫu, thứ tự kênh ADC khi quét
	``` ADC_RegularChannelConfig(ADC_TypeDef* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime); ```
	- Rank: Ưu tiên của kênh ADC
 	- Sample Time: Thời gian lấy mẫu tín hiệu
- Hàm bắt đầu quá trình chuyển đổi:
	``` ADC_SoftwareStartConvCmd(ADC_TypeDef* ADCx, FunctionalState NewState); ```
- Hàm đọc giá trị chuyển đổi được ở các kênh ADC tuần tự
	``` ADC_GetConversionValue(ADC_TypeDef* ADCx); ```
- Hàm trả về giá trị chuyển đổi cuối cùng của ADC1, ADC2 ở chế độ kép
	``` ADC_GetDualModeConversionValue(void); ```
**Hàm cấu hình ADC đầy đủ**
```
void ADC_Config(){
	ADC_InitTypeDef ADC_InitStruct;
	
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	}
```

Ví dụ: Dùng cách tính trung bình mỗi 10 lần đọc để tính điện áp chân PA0 sau mỗi giây.
Lời giải:
```
while(1){
		for(int i=0; i<10; i++){
			val = ADC_GetConversionValue(ADC1);
			delay_us(100);
			sum+=val;
		}
		sum = sum/10;
		Delay_Ms(100);
sum=0;
	}
```
 Tuy nhiên, giá trị đo được trên ADC có thể bị nhiễu, vọt lố do nhiều lý do khách quan về phần cứng. Phương pháp trung bình không thể giảm thiểu các giá trị này. Do đó không thực tế để ứng dụng. Để giải quyết vấn đề này, chúng ta sử dụng **thuật toán lọc Kalman**.

----------------------------------------------------------
<a name="Lesson6"></a>
## **LESSON 6: CONTROLLER AREA NETWORK (CAN)**
	
