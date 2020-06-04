                                /*...............................RSA encrypter system...................................*/

#include<stdio.h>
#include<gmp.h>

mpz_t plain_text,cipher_text,b_pub_key,n_p_mul_q;
char ch_pl_txt[500],ch_b_txt[500],ch_n_txt[500];

void square_and_mult_modulo_gmp(mpz_t,mpz_t,mpz_t);


int main()
{

int j;

printf("RSA encrypter system\nEnter your plain text here to encrypt\n");
scanf("%s",ch_pl_txt);

printf("Enter receivers public encyption key b_pub_key :  ");
scanf("%s",ch_b_txt);

printf("Enter receivers public encyption key n_p_mult_q :  ");
scanf("%s",ch_n_txt);

j=mpz_init_set_str(plain_text,ch_pl_txt,0);
j=mpz_init_set_str(b_pub_key,ch_b_txt,0);
j=mpz_init_set_str(n_p_mul_q,ch_n_txt,0);

square_and_mult_modulo_gmp(plain_text,b_pub_key,n_p_mul_q);

gmp_printf("cipher text is :  %Zd\n",cipher_text);

return 0;

}


/*generates parameter1 to the power parameter2 modulo parameter3 using square multiply method*/

void square_and_mult_modulo_gmp(mpz_t x,mpz_t c,mpz_t n)
{

mpz_t z,c_copy;
int c_bin[5000],i=0,l=0;
unsigned long int junk;

mpz_init(z);
mpz_init(c_copy);

mpz_add_ui (z,z,1);
mpz_set(c_copy,c);

while(mpz_cmp_ui(c_copy,0)!=0)
{

c_bin[i]=mpz_odd_p(c_copy);
junk=mpz_fdiv_q_ui(c_copy,c_copy,2);

i++;
l++;

}

for(i=l-1;i>=0;i--)
{

mpz_mul(z,z,z);
mpz_mod(z,z,n);

if(c_bin[i]!=0)
mpz_mul(z,z,x);
mpz_mod(z,z,n);

}

mpz_set(cipher_text,z);
mpz_clear(c_copy);

}

