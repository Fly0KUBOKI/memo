#include "gpio.h"
#include "usart.h"
#include <string>
#include <vector>

using namespace std;

void serial_char(const char *a){
	std::string str;
	str = a;
	HAL_UART_Transmit(&huart2, (uint8_t *)str.c_str(),str.length(),100);
}

void serial_mat (vector<vector<float>> x){
	unsigned int m,n,i,j;
	std::string str;

	m = x.size();
	n = x[0].size();

	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			str += std::to_string((int)x[i][j]);
			str += "   ";
		}
		HAL_UART_Transmit(&huart2, (uint8_t *)str.c_str(),str.length(),100);
		str = "\n";
	}
	str += "\n";
	HAL_UART_Transmit(&huart2, (uint8_t *)str.c_str(),str.length(),100);



}
