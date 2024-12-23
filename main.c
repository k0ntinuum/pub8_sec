#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constant.c"
#include "text.c"
#include "bin.c"
#include "print.c"
#include "random.c"
#include "F.c"
#include "compute.c"



int main() {
    cls();
    int x = 34;
    int B[Y*Y][Z];
    int P[Y*Y][Z];
    int x_bin[Y];
    int d_bin[Y];
    int y_bin[Y*Y];
    int z_bin[Y*Y];
    int y[Y] = {0};
    int d;
    int p[Z];
    int n[Z];
    int M[Y][Z] = {0};
    int T[Y][X];
    int TC[Y][X];
    int S[Y][X];
    int SC[Y][X];
    int F[Y][Z];
    int chi_S[Y][Z];
    int chi_T[Y][Z];
    int code[Y];
    int q[Y*Y];
    int q_inv[Y*Y];
    int Q[Y*Y][Y];
    int Q_inv[Y*Y][Y];
    //for (int i = 0; i < F_len; i++) n[i] = i;
    create_perm(q,Y*Y);
    create_perm(p, Z);
    invert(q, q_inv, Y*Y);
    test_inverse(q, q_inv);
    create_M(M, p);
    print_M(M);printf("\n\n");
    for (int i = 0; i < Y; i++)  create_T_set(T[i], M, i);
    for (int i = 0; i < Y; i++)  create_comp(T[i], TC[i]);
    for (int i = 0; i < Y; i++)  disjoint(T[i],TC[i]);
    for (int i = 0; i < Y; i++)  create_S_set(S[i]);
    for (int i = 0; i < Y; i++)  create_comp(S[i], SC[i]);
    for (int i = 0; i < Y; i++)  disjoint(S[i],SC[i]);
    for (int i = 0; i < Y; i++)  create_chi(S[i], chi_S[i]);
    for (int i = 0; i < Y; i++)  create_chi(T[i], chi_T[i]);
    for (int i = 0; i < Y; i++)  print_chi(chi_T[i]);
    for (int i = 0; i < Y; i++)  print_chi(chi_S[i]);

    for (int i = 0; i < Y; i++)  create_F(T[i], TC[i], S[i], SC[i], F[i]);
    create_Q(q,Q);
    //print_Q(Q);
    //printf("\n");
    //create_Q(q_inv,Q_inv);
    //print_Q(Q_inv);
    //printf("\n");
    create_B(F, B);
    //print_B(B);
    //printf("\n");
    create_P(q, B, P);
    print_B(P);
    printf("\n\n");
    
    for (x = 0; x < 256; x++) {
        write_x_bin(x, x_bin);
        enc_B( P , x_bin, y_bin);
        dec_P( chi_S, M, q_inv, y_bin, d_bin);
        print_enc_bin(x_bin,y_bin);printf("\n");
        //print_dec_bin(d_bin, y_bin);printf("\n\n");
        if (!vec_equal(x_bin, d_bin, Y)) printf("\nFAILURE TO DECODE\n");
    }
    

    //print_F(F[0]);


    
}
      