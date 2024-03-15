# **EMBEDDED IN AUTOMOTIVE**

### **MỤC LỤC**

[LESSON 1: GENERAL PURPOSE INPUT OUTPUT](#Lesson1)

[LESSON 2: INTERRUPT & TIMER](#Lesson2)

[LESSON 3: BASIC COMMUNICATION STANDARDS](#Lesson3)

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

	        Output Push Pull  : Cho phép tùy chỉnh tín hiệu ở 2 mức logic 0 (0V) và 1 (3,3V)'
		    Output Open Drain : Thiếp lập đấu ra có tín hiệu 0V và thả nổi 0-3,3V (đoạn này chưa rõ lắm)'
	
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
	
<a name="Lesson2"></a>
## **LESSON 2: INTERRUPT & TIMER**	
	
<a name="Lesson3"></a>
## **LESSON 3: BASIC COMMUNICATION STANDARDS**	
	
	
