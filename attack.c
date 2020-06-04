                           /*.................................Wiener's low decryption attack......................................*/

#include<stdio.h>
#include<gmp.h>

void eucldean();
int wiener();

mpz_t b_pub_key,n_p_mul_q,n_cpy,r[1000],q[1000],p_prime,q_prime;
int m;

int main()
{

int i;
char ch_b_txt[500],ch_n_txt[500];

printf("RSA attacking system\nEnter the b_pub_key:  ");
scanf("%s",ch_b_txt);

i=mpz_init_set_str(b_pub_key,ch_b_txt,0);

printf("Enter receivers public encyption key n_p_mult_q :  ");
scanf("%s",ch_n_txt);

i=mpz_init_set_str(n_p_mul_q,ch_n_txt,0);

mpz_init(p_prime);
mpz_init(q_prime);
mpz_init(n_cpy);
mpz_set(n_cpy,n_p_mul_q);

eucldean();
i=wiener();

gmp_printf("The first prime is:  %Zd\nThe second prime is :  %Zd\n",p_prime,q_prime);
return 0;

}


void eucldean()
{

mpz_init(r[0]);
mpz_init(r[1]);

mpz_set(r[0],b_pub_key);
mpz_set(r[1],n_p_mul_q);
m=1;

while(mpz_cmp_ui(r[m],0)!=0)
{

mpz_init(r[m+1]);
mpz_init(q[m]);
mpz_fdiv_qr(q[m],r[m+1],r[m-1],r[m]);
m++;

}

m--;


}


int wiener()
{

mpz_t c_arr[1000],d_arr[1000],nn,k1,k2,k3,res,b_eq,b_eq_sq;
int j;
unsigned long int x;

mpz_init(c_arr[0]);
mpz_init(c_arr[1]);
mpz_init(d_arr[0]);
mpz_init(d_arr[1]);

mpz_init(k1);
mpz_init(k2);
mpz_init(k3);
mpz_init(nn);
mpz_init(res);
mpz_init(b_eq);
mpz_init(b_eq_sq);

mpz_set_ui(c_arr[0],1);
mpz_set(c_arr[1],q[1]);
mpz_set_ui(d_arr[0],0);
mpz_set_ui(d_arr[1],1);

for(j=2;j<=m;j++)
{

mpz_init(c_arr[j]);
mpz_init(d_arr[j]);

mpz_mul(k1,q[j],c_arr[j-1]);
mpz_add(c_arr[j],k1,c_arr[j-2]);

mpz_mul(k2,q[j],d_arr[j-1]);
mpz_add(d_arr[j],k2,d_arr[j-2]);

mpz_mul(k3,d_arr[j],b_pub_key);
mpz_sub_ui(k3,k3,1);

mpz_fdiv_r(res,k3,c_arr[j]);

if(mpz_cmp_ui(res,0)==0)
{

mpz_fdiv_q(nn,k3,c_arr[j]);

mpz_sub(b_eq,nn,n_p_mul_q);
mpz_sub_ui(b_eq,b_eq,1);

mpz_mul(b_eq_sq,b_eq,b_eq);
mpz_submul_ui(b_eq_sq,n_p_mul_q,4);

mpz_sqrt(k1,b_eq_sq);

mpz_sub(k2,k1,b_eq);
x=mpz_fdiv_q_ui(p_prime,k2,2);

mpz_neg(k1,k1);
mpz_sub(k3,k1,b_eq);
x=mpz_fdiv_q_ui(q_prime,k3,2);

mpz_set(n_cpy,n_p_mul_q);
mpz_submul(n_cpy,p_prime,q_prime);

if(mpz_cmp_ui(n_cpy,0)==0)
return 0;

}

}

printf("\nfailure\n");
return 0;

}
