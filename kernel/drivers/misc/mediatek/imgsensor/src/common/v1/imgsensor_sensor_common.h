#ifndef _IMGSENSOR_SENSOR_COMMON_H
#define _IMGSENSOR_SENSOR_COMMON_H

#define IMGSENSOR_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define IMGSENSOR_LINGLENGTH_GAP 80


struct imgsensor_i2c_reg {
	kal_uint16 addr;
	kal_uint16 data;
	kal_uint16 delay;
};

enum imgsensor_i2c_addr_type{
	IMGSENSOR_I2C_BYTE_ADDR = 1,
	IMGSENSOR_I2C_WORD_ADDR,
	IMGSENSOR_I2C_ADDR_MAX,
};

enum imgsensor_i2c_data_type {
	IMGSENSOR_I2C_BYTE_DATA = 1,
	IMGSENSOR_I2C_WORD_DATA,
	IMGSENSOR_I2C_DATA_MAX,
};

enum imgsensor_i2c_operation {
	IMGSENSOR_I2C_WRITE,
	IMGSENSOR_I2C_READ,
	IMGSENSOR_I2C_POLL,
};

struct imgsensor_i2c_reg_table{
	kal_uint16 addr;
	kal_uint16 data;
	enum imgsensor_i2c_data_type data_type;
	enum imgsensor_i2c_operation i2c_operation;
	kal_uint16 delay;
};

typedef struct imgsensor_i2c_reg_table_array{
	struct imgsensor_i2c_reg_table *setting;
	kal_uint16 size;
}imgsensor_i2c_reg_table_array_t;

//��ʾsensor�ļ��ֹ���ģʽ״̬��init preview capture video hvideo svideo
typedef enum{
	IMGSENSOR_MODE_INIT,
	IMGSENSOR_MODE_PREVIEW,
	IMGSENSOR_MODE_CAPTURE,
	IMGSENSOR_MODE_VIDEO,
	IMGSENSOR_MODE_HIGH_SPEED_VIDEO,
	IMGSENSOR_MODE_SLIM_VIDEO,
	IMGSENSOR_MODE_CUSTOM1,
	IMGSENSOR_MODE_CUSTOM2,
	IMGSENSOR_MODE_CUSTOM3,
	IMGSENSOR_MODE_CUSTOM4,
	IMGSENSOR_MODE_CUSTOM5,
} imgsensor_common_mode_t;

//��ʾ���֣���ͬ����ģʽ״̬�£���sensor������Ϣ
typedef struct {
	kal_uint32 pclk;               //record different mode's pclk
	kal_uint32 linelength;         //record different mode's linelength
	kal_uint32 framelength;	       //record different mode's framelength

	kal_uint8 startx;              //record different mode's startx of grabwindow
	kal_uint8 starty;              //record different mode's startx of grabwindow

	kal_uint16 grabwindow_width;   //record different mode's width of grabwindow
	kal_uint16 grabwindow_height;  //record different mode's height of grabwindow

	/*   following for MIPIDataLowPwr2HighSpeedSettleDelayCount by different scenario   */
	kal_uint8 mipi_data_lp2hs_settle_dc;

	/*   following for GetDefaultFramerateByScenario()  */
	kal_uint16 max_framerate;
	kal_uint32 mipi_pixel_rate;
	kal_uint32 mipi_trail_val;
} imgsensor_mode_info_t;

typedef struct imgsensor_i2c_reg_setting{
	struct imgsensor_i2c_reg *setting;
	kal_uint16 size;
	enum imgsensor_i2c_addr_type addr_type;
	enum imgsensor_i2c_data_type data_type;
	kal_uint16 delay;
}imgsensor_i2c_reg_setting_t;

//��ʾ����ǰ״̬����ģʽ���µ�sensor������Ϣ
/* SENSOR PRIVATE STRUCT FOR VARIABLES*/
typedef struct {
	kal_uint8 mirror;               //mirrorflip information
	kal_uint8 sensor_mode;          //record IMGSENSOR_MODE enum value
	kal_uint32 shutter;             //current shutter
	kal_uint16 gain;                //current gain
	kal_uint32 pclk;                //current pclk
	kal_uint32 frame_length;        //current framelength
	kal_uint32 line_length;         //current linelength
	kal_uint32 min_frame_length;    //current min  framelength to max framerate
	kal_uint16 dummy_pixel;         //current dummypixel
	kal_uint16 dummy_line;          //current dummline
	kal_uint16 current_fps;         //current max fps
	kal_bool   autoflicker_en;      //record autoflicker enable or disable
	kal_bool test_pattern;          //record test pattern mode or not
	enum MSDK_SCENARIO_ID_ENUM current_scenario_id;//current scenario id
	kal_bool  ihdr_en;              //ihdr enable or disable
	kal_uint8 i2c_write_id;         //record current sensor's i2c write id
	kal_uint32  i2c_speed;     //i2c speed
	enum imgsensor_i2c_addr_type addr_type;
} imgsensor_t;

//sensor������Ϣ��datasheet�ϵ���Ϣ
/* SENSOR PRIVATE STRUCT FOR CONSTANT*/
typedef struct {
	kal_uint16 sensor_id_reg;           //sensor chip id reg addr
	kal_uint32 sensor_id;               //record sensor id defined in Kd_imgsensor.h
	kal_uint32 checksum_value;          //checksum value for Camera Auto Test
	imgsensor_mode_info_t pre;          //preview scenario relative information
	imgsensor_mode_info_t cap;          //capture scenario relative information
	imgsensor_mode_info_t cap1;         //capture for PIP 24fps relative information, capture1 mode must use same framelength, linelength with Capture mode for shutter calculate
	imgsensor_mode_info_t normal_video; //normal video  scenario relative information
	imgsensor_mode_info_t hs_video;     //high speed video scenario relative information
	imgsensor_mode_info_t slim_video;   //slim video for VT scenario relative information
	imgsensor_mode_info_t custom1;      //custom1 scenario relative information
	imgsensor_mode_info_t custom2;      //custom2 scenario relative information
	imgsensor_mode_info_t custom3;      //custom3 scenario relative information
	imgsensor_mode_info_t custom4;      //custom4 scenario relative information
	imgsensor_mode_info_t custom5;      //custom5 scenario relative information

	imgsensor_i2c_reg_setting_t init_setting;
	imgsensor_i2c_reg_setting_t pre_setting;
	imgsensor_i2c_reg_setting_t cap_setting;
	imgsensor_i2c_reg_setting_t cap1_setting;
	imgsensor_i2c_reg_setting_t normal_video_setting;
	imgsensor_i2c_reg_setting_t hs_video_setting;
	imgsensor_i2c_reg_setting_t slim_setting;
	imgsensor_i2c_reg_setting_t custom1_setting;
	imgsensor_i2c_reg_setting_t custom2_setting;
	imgsensor_i2c_reg_setting_t custom3_setting;
	imgsensor_i2c_reg_setting_t custom4_setting;
	imgsensor_i2c_reg_setting_t custom5_setting;
	imgsensor_i2c_reg_setting_t streamon_setting;
	imgsensor_i2c_reg_setting_t streamoff_setting;
	imgsensor_i2c_reg_setting_t test_pattern_on_setting;
	imgsensor_i2c_reg_setting_t test_pattern_off_setting;

	imgsensor_i2c_reg_table_array_t dump_info;

	kal_uint8  ae_shut_delay_frame; //shutter delay frame for AE cycle
	kal_uint8  ae_sensor_gain_delay_frame;  //sensor gain delay frame for AE cycle
	kal_uint8  ae_ispGain_delay_frame;  //isp gain delay frame for AE cycle
	kal_uint8  ihdr_support;        //1, support; 0,not support
	kal_uint8  ihdr_le_firstline;   //1,le first ; 0, se first
	kal_uint8  sensor_mode_num;     //support sensor mode num

	kal_uint8  cap_delay_frame;     //enter capture delay frame num
	kal_uint8  pre_delay_frame;     //enter preview delay frame num
	kal_uint8  video_delay_frame;   //enter video delay frame num
	kal_uint8  hs_video_delay_frame;    //enter high speed video  delay frame num
	kal_uint8  slim_video_delay_frame;  //enter slim video delay frame num
	kal_uint8  custom1_delay_frame;     //enter custom1 delay frame num
	kal_uint8  custom2_delay_frame;     //enter custom1 delay frame num
	kal_uint8  custom3_delay_frame;     //enter custom1 delay frame num
	kal_uint8  custom4_delay_frame;     //enter custom1 delay frame num
	kal_uint8  custom5_delay_frame;     //enter custom1 delay frame num

	kal_uint8  margin;              //sensor framelength & shutter margin
	kal_uint32 min_shutter;         //min shutter
	kal_uint32 max_frame_length;    //max framelength by sensor register's limitation

	kal_uint8  isp_driving_current; //mclk driving current
	kal_uint8  sensor_interface_type;//sensor_interface_type
	kal_uint8  mipi_sensor_type; //0,MIPI_OPHY_NCSI2; 1,MIPI_OPHY_CSI2, default is NCSI2, don't modify this para
	kal_uint8  mipi_settle_delay_mode; //0, high speed signal auto detect; 1, use settle delay,unit is ns, default is auto detect, don't modify this para
	kal_uint8  sensor_output_dataformat;//sensor output first pixel color
	kal_uint8  mclk;                //mclk value, suggest 24 or 26 for 24Mhz or 26Mhz

	kal_uint8  mipi_lane_num;       //mipi lane num
	kal_uint8  i2c_addr_table[5];   //record sensor support all write id addr, only supprt 4must end with 0xff
	kal_uint32  i2c_speed;     //i2c speed
	enum imgsensor_i2c_addr_type addr_type;
} imgsensor_info_t;

MUINT32 imgsensor_convert_sensor_id(MUINT32 imgsensor_sensor_id,MUINT32 sensor_chip_id,
                                        MUINT32 vendor_id_addr, MUINT32 product_id);
#endif