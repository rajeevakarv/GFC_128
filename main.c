unsigned int irreducible_poly[4] = { 0xE1000000, 0x000000000, 0x00000000, 0x00000000 };
//unsigned int num1[4] = {0x0388dace, 0x60b6a392, 0xf328c2b9, 0x71b2fe78};
//unsigned int num2[4] = {0x66e94bd4, 0xef8a2c3b, 0x884cfa59, 0xca342b2e};

//unsigned int num1[4] = {0x5e2ec746, 0x91706288, 0x2c85b068, 0x5353de37};
//unsigned int num2[4] = {0x66e94bd4, 0xef8a2c3b, 0x884cfa59, 0xca342b2e};
//Z2 = [f38cbb1ad69223dcc3457ae5b6b0f885]

//unsigned int num1[4] = {0xba471e04, 0x9da20e40, 0x495e28e5, 0x8ca8c555};
unsigned int num1[4] = {0x42831ec2, 0x21777424, 0x4b7221b7, 0x84d0d49c};
unsigned int num2[4] = {0xb83b5337, 0x08bf535d, 0x0aa6e529, 0x80d53b78};
//Z3 = [b714c9048389afd9f9bc5c1d4378e052]


unsigned int mult_result[4] = {0};
void right_shift(void)
{
    unsigned char i;
    unsigned int temp[3] = {0};
    for (i=0; i<3; i++)
	temp[i] = num1[i] & 0x01;
    num1[0] = num1[0]>>1;
    for (i=1; i<4; i++)
        num1[i] = (num1[i]>>1)| temp[i-1]<<31;
}

void left_shift(void)
{
    unsigned char i;
    unsigned int temp[4] = {0};
    for (i=0; i<4; i++)
	temp[i] = num2[i] & 0x80000000;
    num2[3] = num2[3]<<1;
    for (i=0; i<3; i++)
        num2[i] = ((num2[i]<<1)| temp[i+1]>>31)&0xFFFFFFFF;
}

void mod_function()
{
    unsigned char i;
    for(i=0; i<4; i++)
	num1[i] = num1[i]^irreducible_poly[i];
}

void gmultiplication(void) {

        unsigned int OutOfRange;
        unsigned int i,j;
        for (i = 0; i < 128; i++) {
                if (num2[0] & 0x80000000)
		{
                       for(j=0; j<4; j++)
		            mult_result[j] = mult_result[j] ^ num1[j];
		}
		OutOfRange = (num1[3] & 0x1);
                right_shift(); 
                if (OutOfRange)
                        mod_function();
                left_shift(); 
		
        }
        //return temp;
}

int main()
{
    int i;
//	printf("Val = 0x%x  0x%x  0x%x 0x%x \n", num1[0], num1[1], num1[2], num1[3]);
	gmultiplication();
	printf("Val = 0x%x  0x%x  0x%x 0x%x \n", mult_result[0], mult_result[1], mult_result[2], mult_result[3]);

}
