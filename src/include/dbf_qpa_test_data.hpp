#ifndef dbf_qpa_test_data_struct
#define dbf_qpa_test_data_struct

struct DBF_QPA_TEST_DATA{
	bool feasible;
	long long sum_qpa_points;
	long long sum_dbf_points;

	DBF_QPA_TEST_DATA(){
		feasible = false;
		sum_qpa_points = 0;
		sum_dbf_points = 0;
	}
};

#endif