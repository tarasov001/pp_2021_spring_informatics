// Copyright 2021 Kumbrasev Mark
#include "../../../modules/task_1/kumbrasev_m_conjugate_gradient/conjugate_gradient.h"

const double nzero = 1.0e-10;

vector<double> linVec( double a, const vector<double> &v1, double b, const vector<double> &v2 ) {
   int n = v1.size();
   vector<double> v3( n );
   for ( int i = 0; i < n; i++ ) {
      v3[i] = a * v1[i] + b * v2[i];
   }
   return v3;
}

double innerVec( const vector<double> &v1, const vector<double> &v2 ) {
   return inner_product( v1.begin(), v1.end(), v2.begin(), 0.0 );
}

vector<double> mMultv( const vector<vector<double>> &M, const vector<double> &V ) {
   int n = M.size();
   vector<double> C( n );
   for ( int i = 0; i < n; i++ ) {
      C[i] = innerVec( M[i], V );
   }
   return C;
}

double vecNorm( const vector<double> &V ) {
   return sqrt( innerVec( V, V ) );
}

vector<double> ConjugateGradient( const vector<vector<double>> &M, const vector<double> &B ) {
   int n = M.size();

   vector<double> X( n, 0.0 );

   vector<double> R = B;
   vector<double> P = R;
   int k = 0;

   while ( k < n ) {
      vector<double> Rold = R;
      vector<double> MP = mMultv( M, P );

      double alpha = innerVec( R, R ) / max( innerVec( P, MP ), nzero );
      X = linVec( 1.0, X, alpha, P );
      R = linVec( 1.0, R, -alpha, MP );

      if ( vecNorm( R ) < nzero ) {
         break;
      }

      double beta = innerVec( R, R ) / max( innerVec( Rold, Rold ), nzero );
      P = linVec( 1.0, R, beta, P );
      k++;
   }

   return X;
}
