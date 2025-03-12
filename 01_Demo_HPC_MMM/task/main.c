#include "matrix.h"
#include "timing.h"
#define NO_MEASURE_FLOP
#define no_limitcheck
void matrix_init(matrix * this, int * dims)
{
    int i,k;
    this->dims[0]=dims[0];
    this->dims[1]=dims[1];
    size_t msize=this->dims[0] * this->dims[1] *sizeof(double);
    this->val = malloc(msize);
    double (*dval)[this->dims[0]][this->dims[1]]=this->val;
    for (k=0; k<this->dims[0]; ++k)
    {
        for (i=0; i<this->dims[1]; ++i)
        {
            (*dval)[k][i]=0.0;
        }
    }
}
void matrix_kill(matrix * this)
{
    free(this->val);
    free(this);
}
matrix * matrix_new(int * dims)
{
    matrix * n;
    n = malloc(sizeof(matrix));
    matrix_init(n,dims);
    return n;
}
void matrix_fill_row(matrix * this, int colIdx,double * arr)
{
    double (*dval)[this->dims[0]][this->dims[1]]=this->val;
    int i;
    for (i=0; i<this->dims[1]; ++i)
    {
        (*dval)[colIdx][i]=arr[i];
    }
}
void matrix_print(matrix * this)
{
    int i,k;
    double (*dval)[this->dims[0]][this->dims[1]]=this->val;
    for (k=0; k<this->dims[0]; ++k)
    {
        for (i=0; i<this->dims[1]; ++i)
        {
            printf("%f, ",(*dval)[k][i]);
        }
        printf("\n");
    }
}
void  matrix_multiply(matrix * pm1, matrix * pm2, matrix * res)
{
#ifdef limitcheck
    if (pm1->dims[1]==pm2->dims[0])
    { 
#endif
        double (*m1)[pm1->dims[0]][pm1->dims[1]]=pm1->val;
        double (*m2)[pm2->dims[0]][pm2->dims[1]]=pm2->val;
        double (*r)[res->dims[0]][res->dims[1]]=res->val;
        int i,k,l;
#ifdef MEASURE_FLOP
        long unsigned int flop=0;
#endif 
        double sum=0.0; //1FLOP
#ifdef MEASURE_FLOP
        flop++;
#endif 
        for (k=0; k<pm1->dims[0]; ++k)
        {
            for(l=0; l<pm2->dims[1]; ++l)
            {
                for (i=0; i<pm1->dims[1]; ++i)
                {
                }
            }
        }
#ifdef MEASURE_FLOP
        printf("Number of flops per loop: %lu\n",flop);
#endif
#ifdef limitcheck
    }
#endif
}
int main()
{
    long unsigned int i;
    long unsigned int LIMIT=100000000UL;
    int M1_ext[2]= {2,3};
    int M2_ext[2]= {3,2};
    double wcTimeStart;
    double wcTimeEnd;
    matrix *M1, *M2, *res;
    M1 = matrix_new(M1_ext);
    M2 = matrix_new(M2_ext);
    int res_dim[2]= {M1->dims[0],M2->dims[1]};
    double m1_row1[3]= {1.0,2.0,3.0};
    double m1_row2[3]= {4.0,5.0,6.0};
    double m2_row1[2]= {7.0,8.0};
    double m2_row2[2]= {9.0,10.0};
    double m2_row3[2]= {11.0,12.0};
    matrix_fill_row(M1, 0,m1_row1);
    matrix_fill_row(M1, 1,m1_row2);
    matrix_fill_row(M2, 0,m2_row1);
    matrix_fill_row(M2, 1,m2_row2);
    matrix_fill_row(M2, 2,m2_row3);
//    matrix_print(M1);
//    matrix_print(M2);
    res=matrix_new(res_dim);
    timing(&wcTimeStart);
    for (i=0;i<LIMIT;++i)
    {
        matrix_multiply(M1,M2,res);
    }
    timing(&wcTimeEnd);
    matrix_print(res);
    matrix_kill(M1);
    matrix_kill(M2);
    matrix_kill(res);
    printf("TimeEnd: %f\n",wcTimeEnd);
    printf("RunTime: %f\n",wcTimeEnd-wcTimeStart);
		// replace 999.0 with the actual number of FLOPs in a call to matrix_multiply
    printf("MFLOPS: %f\n",999.0*((double)LIMIT/(double)1000000UL)/(wcTimeEnd-wcTimeStart));
    return 0;
}
