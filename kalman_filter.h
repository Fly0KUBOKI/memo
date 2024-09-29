#ifndef INC_KALMAN_H_
#define INC_KALMAN_H_

#define ARM_MATH_CM4
#include "arm_math.h"
#include "arm_const_structs.h"

unsigned short int i,j,c;


void mat31cal(float x[3][3],float y[3][1],float answer[3][1]){
	arm_matrix_instance_f32 A ={3,3,(float32_t *)x};
	arm_matrix_instance_f32 B ={3,1,(float32_t *)y};
	arm_matrix_instance_f32 C ={3,1,(float32_t *)answer};
	arm_mat_mult_f32(&A,&B,&C);
}


void mat33cal(float x[][3],float y[][3],float answer[][3],unsigned short int c){
	arm_matrix_instance_f32 A ={3,3,(float32_t *)x};
	arm_matrix_instance_f32 B ={3,3,(float32_t *)y};
	arm_matrix_instance_f32 C ={3,3,(float32_t *)answer};
	switch(c){
	case 1: arm_mat_add_f32(&A,&B,&C); break;
	case 2: arm_mat_sub_f32(&A,&B,&C); break;
	case 3: arm_mat_mult_f32(&A,&B,&C); break;
	case 4: arm_mat_trans_f32(&A,&C); break;
	case 5: arm_mat_inverse_f32(&A,&C); break;
	}
}


void matcal3(float x[][3],float y[][3],float z[][3],float answer[][3]){

	arm_matrix_instance_f32 A ={3,3,(float32_t *)x};
	arm_matrix_instance_f32 B ={3,3,(float32_t *)y};
	arm_matrix_instance_f32 C ={3,3,(float32_t *)z};
	arm_matrix_instance_f32 D ={3,3,(float32_t *)answer};
	float buf[3][3];
	arm_matrix_instance_f32 E ={3,3,(float32_t *)buf};
	arm_mat_mult_f32(&A,&B,&E);
	arm_mat_mult_f32(&E,&C,&D);
}

void mat11cal(float x[3][1],float y[3][1],float answer[3][1],unsigned short int c){
	switch(c){
	case 1:
		for (i=0;i<3;i++){
			answer[i][0] = x[i][0] + y[i][0];
		}; break;
	case 2:
		for (i=0;i<3;i++){
			answer[i][0] = x[i][0] - y[i][0];
		}; break;
	}

}

void mat31change(float x[3][1],float y[3][1]){

	for (i=0;i<3;i++){
		y[i][0] = x[i][0];
	}

}



void mat33change(float x[3][3],float y[3][3]){

	for (i=0;i<3;i++){
		for (j=0;j<3;j++){
			y[i][j] = x[i][j];
		}
	}

}

void kalman(float S[][3]){

		//mat31change(X1,X);
		//mat33change(P1,P);
			S[0][0] = 1; S[0][1] = 0; S[0][2] = 0;
			S[1][0] = 0; S[1][1] = 1; S[1][2] = 0;
			S[2][0] = 0; S[2][1] = 0; S[2][2] = 1;

	float ax,ay,az,  mx,my,mz,  wx,wy,wz,  thx=0,thy=0,thz=0;
	float X[3][1] ,Xh[3][1] ,y[3][1];
	float A[3][3] ,At[3][3];
	float Q[3][3] = {{0.01,0,0},{0,0.01,0},{0,0,0.01}};
	float R[3][3] = {{0.1,0,0},{0,0.1,0},{0,0,0.1}};
	float SQ[3][3],SR[3][3];
	float C[3][3] = {{1,0,0},{0,1,0},{0,0,1}} ,Ct[3][3];
	float I[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

	float K[3][3];
	float buf,buf1[3][3],buf2[3][3],buf3[3][1],buf31[3][1];
	float t = 1;

		//Xh[0][0] = thx + (wx + wy*tan(thy)*sin(thx) + wz*tan(thy)*cos(thx)) * t;
		//Xh[1][0] = thy + (wy*cos(thx) - wz*sin(thx)) * t;
		//Xh[2][0] = thz + (wy*sin(thx)/cos(thy) + wz*cos(thx)/cos(thy)) * t;

		Xh[0][0] = 2.5;
		Xh[1][0] = 2;
		Xh[2][0] = 1;

		//y[0][0] = atan(ay/az);
		//y[1][0] = atan(ax/sqrt(ay*ay + az*az));
		//y[2][0] = atan(( mx*cos(y[1][0])+my*sin(y[1][0])*sin(y[0][0])+mz*sin(y[1][0])*cos(y[0][0]) ) / ( my*cos(y[0][0])-mz*sin(y[0][0]) ));


		y[0][0] = 2;
		y[1][0] = 2;
		y[2][0] = 2;


		//A[0][0] = 1 + ( wx + wx*tan(thy)*cos(thx) - wz*tan(thy)*sin(thx) ) * t;
		//A[0][1] = ( wy*sin(thx)/cos(thy)/cos(thy) + wz*cos(thx)/cos(thy)/cos(thy) ) * t;
		//A[0][2] = 0;
		//A[1][0] = ( -1*wy*sin(thx) - wz*cos(thx) ) * t;
		//A[1][1] = 1;
		//A[1][2] = 0;
		//A[2][0] = ( wy*cos(thx)/cos(thy) - wz*sin(thx)/cos(thy) ) * t;
		//A[2][1] = ( wy*sin(thx)*sin(thy)/cos(thy)/cos(thy) + wz*cos(thx)*sin(thy)/cos(thy)/cos(thy) ) * t;
		//A[2][2] = 1;


		A[0][0] = 1; A[0][1] = 1; A[0][2] = 0.5;
		A[1][0] = 0; A[1][1] = 1; A[1][2] = 1;
		A[2][0] = 0; A[2][1] = 0; A[2][2] = 1;

		mat33cal(A,0,At,4); //Aの転置
		matcal3(A,S,At,buf1); //1_2_1
		mat33cal(buf1,Q,SQ,1); //1_2_2

		mat33cal(C,0,Ct,4); //Cの転置
		matcal3(C,SQ,Ct,buf1); //2_1_1
		mat33cal(buf1,R,SR,1); //2_1_2
		mat33cal(SR,0,buf1,4); //SRの転置
		matcal3(SQ,Ct,buf1,K); //2_1_3

		mat11cal(y,Xh,buf3,2); //2_2_1
		mat31cal(K,buf3,buf31); //2_2_2
		mat11cal(Xh,buf31,X,1); //2_2_3

		mat33cal(K,C,buf1,3); //2_3_1
		mat33cal(I,buf1,buf2,2); //2_3_2
		mat33cal(buf2,SQ,S,3); //2_3_3

}



#endif /* INC_KALMAN_H_ */
