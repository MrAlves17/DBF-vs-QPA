#ifndef statistical_data_struct
#define statistical_data_struct

struct STATISTICAL_DATA{
	long long sum_qpa_points;
	long long sum_dbf_points;

	STATISTICAL_DATA(){
		sum_qpa_points = 0;
		sum_dbf_points = 0;
	}
};

#endif