int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
	int area1=(C-A)*(D-B);
	int area2=(G-E)*(H-F);

	return area1-getCommonArea(A, B, C, D, E, F, G, H)+area2;
}

int getCommonArea(int A, int B, int C, int D, int E, int F, int G, int H)
{
	int x=getCrossLen(A, C, E, G);
	//printf("[%d, %d] [%d, %d] -> %d\n", A, C, E, G, x);
	int y=getCrossLen(B, D, F, H);
	//printf("[%d, %d] [%d, %d] -> %d\n", B, D, F, H, y);

	return x*y;
}

int getCrossLen(int A, int C, int E, int G)
{
	// 求区间[A, C]和[E, G]的交集
	if(A>E)
	{
		// 保证区间[A, C]在左边
		std::swap(A, E);
		std::swap(C, G);
	}
	if(C<=E)
		return 0;
	if(A<=E  &&  G<=C)
		return G-E;
	if(A<=E  &&  E<=C  &&  C<=G)
		return C-E;
	printf("ERROR %d, %d, %d, %d\n", A, C, E, G);
	return 0;
}