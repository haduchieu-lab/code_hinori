void LCD_INIT(void)
{
	_reset();
	_mode = INIT;

	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo dinh nghi truoc do thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, EN, 1);
	HT1623_SR(S16, EN, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, EN, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, EN, 2);// thanh ghi vong tiep theo dinh nghi truoc do thi cong them 1
	HT1623_SR(R1, EN, 2);
	HT1623_SR(R2, EN, 2);
	HT1623_SR(R3, EN, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	

	_wattage = 88888;
	_ws = 88888;
	_frequence = 888;
	_temperature = 888;
	_voltage_in = 888;
	_voltage_out1 = 888;
	_amp = 8888;
	_mili_amp = 888;
	__start();
}

void LCD_RESET_MODE(void){
	
	
	_reset();
	_mode = RESET;
	
	HT1623_SR(S5, DIS, 0);
	HT1623_SR(S6, DIS, 0);
	HT1623_SR(S7, DIS, 0);
	HT1623_SR(S8, DIS, 0);
	HT1623_SR(S9, DIS, 0);
	HT1623_SR(S10, DIS, 0);
	HT1623_SR(S11, DIS, 0);
	HT1623_SR(S12, DIS, 0);
	
	HT1623_SR(S13, DIS, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, DIS, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, DIS, 1);
	HT1623_SR(S18, DIS, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, DIS, 1);
	
	HT1623_SR(R0, DIS, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, DIS, 2);
	HT1623_SR(R2, DIS, 2);
	HT1623_SR(R3, DIS, 2);	
	HT1623_SR(P1, DIS, 2);
	HT1623_SR(P2, DIS, 2);
	HT1623_SR(P3, DIS, 2);
	HT1623_SR(P4, DIS, 2);

	__start();
}

void LCD_NORMAL_LOADING_MODE(void){
	
	_reset();
	_mode = NORMAL_LOADING;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, EN, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, EN, 2);
	HT1623_SR(R2, EN, 2);
	HT1623_SR(R3, EN, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}

void LCD_ABNORMAL_LOADING_MODE(void)
{
	_reset();
	_mode = NORMAL_LOADING;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, DIS, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, DIS, 2);
	HT1623_SR(R2, DIS, 2);
	HT1623_SR(R3, DIS, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}
void LCD_NORMAL_OVERVOLTAGE_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERVOLTAGE;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, EN, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, EN, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, EN, 2);
	HT1623_SR(R2, EN, 2);
	HT1623_SR(R3, EN, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}
void LCD_ABNORMAL_OVERVOLTAGE_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERVOLTAGE;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, EN, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, DIS, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, DIS, 2);
	HT1623_SR(R2, DIS, 2);
	HT1623_SR(R3, DIS, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}

void LCD_NORMAL_OVERLOAD_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERLOAD;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, EN, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, EN, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, EN, 2);
	HT1623_SR(R2, EN, 2);
	HT1623_SR(R3, EN, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}
void LCD_ABNORMAL_OVERLOAD_MODE(void){
	
	_reset();
	_mode = NORMAL_OVERLOAD;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, DIS, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, EN, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, DIS, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, DIS, 2);
	HT1623_SR(R2, DIS, 2);
	HT1623_SR(R3, DIS, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	_start();
}
void LCD_NORMAL_UNDERVOLTAGE_MODE(void){
	
	_reset();
	_mode = NORMAL_UNDERVOLTAGE;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, EN, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, EN, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, EN, 2);
	HT1623_SR(R2, EN, 2);
	HT1623_SR(R3, EN, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	
	_start();
}


void LCD_ABNORMAL_UNDERVOLTAGE_MODE(void){
	
	_reset();
	_mode = ABNORMAL_UNDERVOLTAGE;
	
	HT1623_SR(S5, EN, 0);
	HT1623_SR(S6, EN, 0);
	HT1623_SR(S7, EN, 0);
	HT1623_SR(S8, EN, 0);
	HT1623_SR(S9, EN, 0);
	HT1623_SR(S10, EN, 0);
	HT1623_SR(S11, EN, 0);
	HT1623_SR(S12, EN, 0);
	
	HT1623_SR(S13, EN, 1);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(S14, EN, 1);
	HT1623_SR(S15, EN, 1);
	HT1623_SR(S16, DIS, 1);
	HT1623_SR(S17, EN, 1);
	HT1623_SR(S18, EN, 1);
	HT1623_SR(S19, DIS, 1);
	HT1623_SR(S20, EN, 1);
	
	HT1623_SR(R0, DIS, 2);// thanh ghi vong tiep theo thi cong them 1
	HT1623_SR(R1, DIS, 2);
	HT1623_SR(R2, DIS, 2);
	HT1623_SR(R3, DIS, 2);	
	HT1623_SR(P1, EN, 2);
	HT1623_SR(P2, EN, 2);
	HT1623_SR(P3, EN, 2);
	HT1623_SR(P4, EN, 2);
	
	

	_start();
}

void LCD_GRAPH(void){
	if(_mode > NORMAL_OVERLOAD || _mode < NORMAL_LOADING)
		return;
	if(_graph_flag == 0){
		HT1623_SR(R1, EN, 2);
		HT1623_SR(R2, DIS, 2);
		HT1623_SR(R3, DIS, 2);
	}
	else if(_graph_flag == 1){
		HT1623_SR(R1, DIS, 2);
		HT1623_SR(R2, EN, 2);
		HT1623_SR(R3, DIS, 2);
	}
	else{
		HT1623_SR(R1, DIS, 2);
		HT1623_SR(R2, DIS, 2);
		HT1623_SR(R3, EN, 2);
	}
	LCD_AMP_IN();
	LCD_VOLTAGE_OUT1();	
}
