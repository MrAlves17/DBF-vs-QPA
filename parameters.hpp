struct PARAMETERS{
	int ntasks, TmaxPerTmin;
	float total_utilization;
	bool dbf, qpa, both;

	PARAMETERS(){
		ntasks = 14;
		TmaxPerTmin = 100;
		total_utilization = 0.70;
		dbf = qpa = both = false;
	}
};