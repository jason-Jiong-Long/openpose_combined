#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "json.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//dirty hacks for higher than implementation
double coor_x[100][18]={[0 ... 99][0 ... 17] = 16384}, coor_y[100][18]={[0 ... 99][0 ... 17] = 16384};
int squat[100]={[0 ... 99] = 0};
int station[100]={[0 ... 99] = 0};
int station_rest[100]={[0 ... 99] = 0};
int station_working[100]={[0 ... 99] = 0};
int station_hand[100]={[0 ... 99] = 0};
int sit_working[100]={[0 ... 99] = 0};
int sit_rest[100]={[0 ... 99] = 0};
int sit_hand[100]={[0 ... 99] = 0};
int sit[100]={[0 ... 99] = 0};
int rest[100]={[0 ... 99] = 0};
int working[100]={[0 ... 99] = 0};
int fall[100]={[0 ... 99] = 0};
int lefthand[100]={[0 ... 99] = 0},righthand[100]={[0 ... 99] = 0}, hand_int[100]={[0 ... 99] = 0};
//implement if needed
//double coor_x_old[100][4]={0}, coor_y_old[100][4]={0};
int num = -1;
int num_old = 0;
char defaultfilename[16] = "_keypoints.json";
char prependfilename[34] = "/home/ele/openpose_combined/json/";
char filenamestring[13] = "000000000000";
char filename[61] = "/home/ele/openpose_combined/json/000000000000_keypoints.json";
long long int file_i = 0;
time_t old_result = 0;
time_t result;
/*
gcc main.c json.c -lm
 */
static void print_depth_shift(int depth)
{
        int j;
        for (j=0; j < depth; j++) {
		//printf(" ");
        }
}
static void output();
char* body_parts(int x);
static void coorx(json_value* value, int x, int y);
static void coory(json_value* value, int x, int y);
static void spit(json_value* value, int x, int y);
static void process_value(json_value* value, int depth, int x);

static void process_object(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.object.length;
        for (x = 0; x < length; x++) {
                print_depth_shift(depth);
                //printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
                process_value(value->u.object.values[x].value, depth+1, x);
        }
}

static void process_array(json_value* value, int depth)
{
        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
        //printf("array: %d\n", depth);
        for (x = 0; x < length; x++) {
                process_value(value->u.array.values[x], depth, x);
        }
}

static void process_value(json_value* value, int depth, int x)
{
        int j;
	char a[100];
        if (value == NULL) {
                return;
        }
        if (value->type != json_object) {
                print_depth_shift(depth);
        }
        switch (value->type) {
                case json_none:
//                printf("none\n");
                        break;
                case json_object:
                        process_object(value, depth+1);
                        break;
                case json_array:
                        process_array(value, depth+1);
                        break;
                case json_integer:
//                        printf("int: %10" PRId64 "\n", value->u.integer);
                        break;
                case json_double:
                        //printf("double: %f\n", value->u.dbl);
					if(x==0)num++;
					//printf("%d",x);
					if(x/3==1 || x/3==2 || x/3==3 || x/3==4 || x/3==5 || x/3==6 || x/3==7 || x/3==8 || x/3==9 || x/3==10 || x/3==12 || x/3==13 || x/3==19 || x/3==20 || x/3==22 || x/3==23){
						switch(x/3){
							case 1:spit(value, x, 0);break;
							case 2:spit(value, x, 1);break;
							case 3:spit(value, x, 2);break;
							case 4:spit(value, x, 3);break;
							case 5:spit(value, x, 4);break;
							case 6:spit(value, x, 5);break;
							case 7:spit(value, x, 6);break;
							case 8:spit(value, x, 7);break;
							case 9:spit(value, x, 8);break;
							case 10:spit(value, x, 9);break;
							case 11:spit(value, x, 10);break;
							case 12:spit(value, x, 11);break;
							case 13:spit(value, x, 12);break;
							case 14:spit(value, x, 13);break;
							case 19:spit(value, x, 14);break;
							case 20:spit(value, x, 15);break;
							case 22:spit(value, x, 16);break;
							case 23:spit(value, x, 17);break;
							default:break;
						}
					}
					//if(num > num_old){
						//printf("hooman[%d], y2=%f, y3=%f, y5=%f, y6=%f\n",num,coor_y[num][0],coor_y[num][1],coor_y[num][2],coor_y[num][3]);
						//num_old++;
					//}
					break;
                case json_string:
//                        printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
//                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}
char* body_parts(int x){
	switch(x/3){
		case 1:return "Neck";
		case 2:return "RShoulder";
		case 3:return "RElbow";
		case 4:return "RWrist";
		case 5:return "LShoulder";
		case 6:return "LElbow";
		case 7:return "LWrist";
		case 8:return "MidHip";
		case 9:return "RHip";
		case 10:return "RKnee";
		case 11:return "RAnkle";
		case 12:return "LHip";
		case 13:return "LKnee";
		case 14:return "LAnkle";
		case 19:return "LBigToe";
		case 20:return "LSmallToe";
		case 22:return "RBigToe";
		case 23:return "RSmallToe";
		default:return "Unimplemented";
	}
}
static void coorx(json_value* value, int x, int y){
	char* part_name=body_parts(x);
	//doing YOLO
	//if(coor_x[num][y]!=0)coor_x_old[num][y]=coor_x[num][y];
	coor_x[num][y]=value->u.dbl;
	//printf("x: %d, coor_x[%d][%d] = %f\n",x/3,num,y,coor_x[num][y]);
	///printf("Person[%d] %s xcoor=%f, x=%d",num,part_name,coor_x[num][y],x);
}
static void coory(json_value* value, int x, int y){
	coor_y[num][y]=value->u.dbl;
  //運算
	double Rslope = ((coor_y[num][8]-coor_y[num][9])/(coor_x[num][8]-coor_x[num][9]));
	double Lslope = ((coor_y[num][11]-coor_y[num][12])/(coor_x[num][11]-coor_x[num][12]));
  double xaxis = pow(coor_x[num][7]-coor_x[num][0],2);
  double yaxis = pow(coor_y[num][7]-coor_y[num][0],2);
  double distance = pow(xaxis+yaxis,0.5);
  double Rslope_xaxis = pow(coor_x[num][9]-coor_x[num][8],2);
  double Rslope_yaxis = pow(coor_y[num][9]-coor_y[num][8],2);
  double Lslope_xaxis = pow(coor_x[num][12]-coor_x[num][11],2);
  double Lslope_yaxis = pow(coor_y[num][12]-coor_y[num][11],2);
  double Rslope_distance = pow(Rslope_xaxis+Rslope_yaxis,0.5);
  double Lslope_distance = pow(Lslope_xaxis+Lslope_yaxis,0.5);
	int sittest = 0;
  int sittest1 = 0;
  int Rstation = 0;
  int Lstation = 0;
  int resttest = 0;
  //坐姿
	if((Rslope >= -1 && Rslope <= 1)||(Lslope >= -1 && Lslope <= 1))sittest=1;
  if(fabs(coor_x[num][7]-coor_x[num][0])<=(distance/2))sittest1 = 1;
	if(fall[num]==0&&sittest==1&&sittest1==1)sit[num]=1;
  //站姿
  if(fabs(coor_x[num][9]-coor_x[num][8])<=(Rslope_distance/2))Rstation = 1;
  if(fabs(coor_x[num][12]-coor_x[num][11])<=(Lslope_distance/2))Lstation = 1;
  if(fall[num]==0 && sittest1==1 && Rstation==1 && Lstation==1 )station[num]=1;
  //舉半手
	if(coor_y[num][3]==16384 && coor_y[num][2]==16384 && coor_y[num][1]==16384){
		//TODO
	}
	else{
		if(fabs(coor_y[num][1]-coor_y[num][3])<=50 && coor_y[num][2]-coor_y[num][1]>=0.5)working[num]=1;
	}
  //蹲姿
//	printf("dbg = %d %f %f %f %f\n", squat[num],coor_y[num][7],coor_y[num][6],coor_y[num][10],coor_y[num][9]);
//	if(coor_x[num][9]==16384 && coor_x[num][8]==16384 && coor_x[num][12] && coor_x[num][11] &&coor_y[num][9]==16384 && coor_y[num][8]==16384 && coor_y[num][12]==16384 && coor_y[num][11]==16384){
//	}else{
//		if(coor_y[num][8] > coor_y[num][9]&&coor_y[num][11] > coor_y[num][12])squat[num]=1;
//	}
  //舉手
	if(coor_y[num][1]-coor_y[num][2]>0.5)righthand[num]=1;
	if(coor_y[num][4]-coor_y[num][5]>0.5)lefthand[num]=1;
  //休息
  if((coor_y[num][3]-coor_y[num][2]>=0.5 && coor_y[num][2]-coor_y[num][1]>=0.5) || (coor_y[num][6]-coor_y[num][5]>=0.5 && coor_y[num][5]-coor_y[num][4])>=0.5)resttest = 1;
	if(working[num]==0 && righthand[num]==0 && lefthand[num]==0 && resttest==1)rest[num]=1;
  //倒下
	if(coor_x[num][0]==16384 || coor_x[num][7]==16384 || coor_y[num][0]==16384 || coor_y[num][7]==16384){
		//skip
		//printf("skip!\n");
	}else{
		double slope = ((coor_y[num][7]-coor_y[num][0])/(coor_x[num][7]-coor_x[num][0]));
		//printf("abcd = %f\n", slope);
		//char* part_name=body_parts(x);
		//YOLO
		//if(coor_y[num][y]!=0)coor_y_old[num][y]=coor_y[num][y];
		//printf("==DEBUG== Human[%d], x1=%f, y1=%f, x8=%f, y8=%f",num,coor_x[num][0],coor_y[num][0],coor_x[num][1],coor_y[num][1]);
		//printf(" x1-x8= %f, y1-y8=%f, Slope = %f\n",(coor_x[num][1]-coor_x[num][0]),(coor_y[num][1]-coor_y[num][0]), slope);

		if(slope >= -1 && slope <= 1)fall[num]=1;
		//if(coor_y[num][2]-coor_y[num][3]>0.5)lefthand[num]=1;
		//printf("x: %d, coor_x[%d][%d] = %f\n",x/3,num,y,coor_y[num][y]);
		//printf(", ycoor=%f, y=%d\n",coor_y[num][y],y),y,coor_y[num][y]);
	}
  //坐姿有問題
	if((sit[num]==1 && righthand[num]==1) || (sit[num]==1 && lefthand[num]==1))sit_hand[num]=1;
  //坐姿工作中
	if(sit[num]==1 && working[num]==1 )sit_working[num]=1;
  //坐姿休息
	if(sit[num]==1 && rest[num]==1 )sit_rest[num]=1;
  //站姿有問題
	if(station[num]==1 && righthand[num]==1 && lefthand[num]==1)station_hand[num]=1;
  //站姿工作中
	if(station[num]==1 && working[num]==1)station_working[num]=1;
  //站姿休息
	if(station[num]==1 && rest[num]==1)station_rest[num]=1;
	if(righthand[num]||lefthand[num]||fall[num]||squat[num]||working[num]||sit[num]||station[num]||station_rest[num]||station_working[num]||station_hand[num]||sit_working[num]||sit_rest[num]||sit_hand[num]||rest[num])output();
}

static void output(){
	//fix for the 0th person is not existent, might need to look into it more
	if(num==0)return;
	//print the results or other stuffs
	result = time(NULL);
	if(fall[num])printf("人類 %d 倒下了！@ %s \n", num, ctime(&result));
//	if(righthand[num])printf("人類 %d 有問題 @ %s！\n", num, ctime(&result));
//	if(lefthand[num])printf("人類 %d 有問題 @ %s！\n", num, ctime(&result));
//	if(squat[num])printf("人類 %d 蹲下了!@ %s \n", num, ctime(&result));
//	if(sit[num])printf("人類 %d 坐著!@ %s \n",num, ctime(&result));
//	if(working[num])printf("人類 %d 工作中!@ %s \n",num, ctime(&result));
	if(sit_hand[num])printf("人類 %d 坐著有問題!@ %s \n",num, ctime(&result));
//	if(sit_working[num])printf("人類 %d 坐著工作中!@ %s \n",num, ctime(&result));
	if(sit_rest[num])printf("人類 %d 坐著休息!@ %s \n",num, ctime(&result));
	if(station_hand[num])printf("人類 %d 站著有問題!@ %s \n",num, ctime(&result));
	if(station_working[num])printf("人類 %d 請勿站著工作!@ %s \n",num, ctime(&result));
	if(station_rest[num])printf("人類 %d 站著休息!@ %s \n",num, ctime(&result));
	//if(ststion[num])printf("人類 %d 站著!@ %s \n",num, ctime(&result));
	//if(rest[num])printf("人類 %d 休息中!@ %s \n",num, ctime(&result));

}

static void spit(json_value* value, int x, int y){
	switch(x%3){
		case 0:coorx(value, x, y);break;
		case 1:coory(value, x, y);break;
		case 2:
		       //confidence, used as counter
		       //printf("x: %d, This is c: %f!\n",x/3,value->u.dbl);

		       break;
		default:break;
	}
}


int main(int argc, char** argv){
	FILE *fp;
	struct stat filestatus;
	int file_size;
	char* file_contents;
	int pollingDelay = 100;
	json_char* json;
	json_value* value;

	for(file_i = 0;file_i < 999999999999; file_i++){
		sprintf(filenamestring, "%012lld", file_i);
		strcpy(filename, prependfilename);
		strcat(filename, filenamestring);
		strcat(filename, defaultfilename);
		//if file not found
		if ( stat(filename, &filestatus) != 0) {
			//printf("Filename: %s\n", filename);
			file_i--;
			#ifdef _WIN32
			Sleep(pollingDelay);
			#else
			usleep(pollingDelay*1000);
			#endif
		}
		else{
			//if OOM
			file_size = filestatus.st_size;
			file_contents = (char*)malloc(filestatus.st_size);
			if ( file_contents == NULL) {
				fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
				return 1;
			}

			//if no read permission
			fp = fopen(filename, "rt");
			if (fp == NULL) {
				fprintf(stderr, "Unable to open %s\n", filename);
				fclose(fp);
				free(file_contents);
				return 1;
			}
			//if unable to read for some reason
			if ( fread(file_contents, file_size, 1, fp) != 1 ) {
				fprintf(stderr, "Unable to read content of %s\n", filename);
			}
			fclose(fp);

			//printf("%s\n", file_contents);

			json = (json_char*)file_contents;

			value = json_parse(json,file_size);

			if (value == NULL) {
				fprintf(stderr, "Unable to parse data\n");
			}

			process_value(value, 0, 0);

			json_value_free(value);
			free(file_contents);

			/*#ifdef _WIN32
			Sleep(pollingDelay);
			#else
			usleep(pollingDelay*1000);
			#endif
			*/
			remove(filename);
			for(int l=0; l<=num; l++){
				for(int n=0; n<16; n++){
					coor_y[l][n] = 16384.0;
					coor_x[l][n] = 16384.0;
				}
				lefthand[l] = 0;
				righthand[l] = 0;
				fall[l] = 0;
				squat[l] = 0;
				sit[l] = 0;
				working[l] = 0;
				station[l] = 0;
				station_rest[l] = 0;
				station_working[l] = 0;
				station_hand[l] = 0;
				sit_working[l] = 0;
				sit_rest[l] = 0;
				sit_hand[l] = 0;
				rest[l] = 0;
			}
			num = -1;
			num_old = 0;
		}
	}

	return 0;
}
