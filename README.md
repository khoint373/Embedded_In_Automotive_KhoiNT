LESSON 1: General Purpose Input Output

Các bước để cấu hình ngoại vi GPIO

B1: Cấp xung cho ngoại vi

Dựa vào Reference Manual hoặc block diagram ta sử dụng hàm và cấp tham số cần thiết:

RCC_(Tên Bus)PerighClockCmd(ngoại vi cần cấu hình, Trạng thái);

Ví dụ: Chúng ta cần cấp xung cho thanh ghi GPIOC, ta thiết lập như sau:

void RCC_Config() {

  RCC_APB2PeriphClockCmd(RCC_APB2Phriph_GPIOC, ENABLE);
  
}

B2: Cấu hình ngoại vi
Sau khi được cấp xung, ta sử dụng hàm GPIO_Init(GPIOx, &GPIO_InitStruct) để cấu hình

Trong đó: GPIOx           : GPIO cần cấu hình
          GPIO_InitStruct : Biến chứa các thông tin để cấu hình cho GPIO
GPIO_InitStruct có kiểu dữ liệu là GPIO_InitTypeDef chứa các trường sau:
          GPIO_Pin        : Chọn Pin đang cần để cấu hình
          GPIO_Mode       : Chọn chế độ cho Pin
          GPIO_Speed      : Chọn tốc độ phản hồi

Nếu cấu hình Pin là đầu vào, ta có thể chọn:
        Input Pull Down   : Thiết lập đầu vào và mức logic ở mức 0 (0V) khi không tác động
        Input Pull Up     : Thiết lập đầu vào và mức logic ở mức 1 (3,3V) khi không tác động
Nếu cấu hình Pin là đầu ra, ta thường sử dụng:
        Output Push Pull  : Cho phép tùy chỉnh tín hiệu ở 2 mức logic 0 (0V) và 1 (3,3V)

Ví dụ: Chúng ta cần cấu hình cho led PC13 và nút bấm PC15

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

B3: Sử dụng ngoại vi
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






