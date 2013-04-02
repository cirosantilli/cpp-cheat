      !standard fortran interface

      subroutine assert_eqi( a, b )

        integer a, b

        if ( a /= b) then
          write(*,*) 'assert_eqi failed'
          write(*,*) 'a', a
          write(*,*) 'b', b
          stop 1
        endif

      end

      subroutine assert_eqr( a, b, err )

        real a, b, err

        if ( abs( a - b ) <= err ) then
          write(*,*) 'assert_eqr failed'
          write(*,*) 'a', a
          write(*,*) 'b', b
          stop 1
        endif

      end

      program main

          !sudo aptitude install liblapack-dev liblapack-doc

        integer n, nrhs, lda, ldb, info, pivots(2)
        real a4(2,2), b2(2), c2(2)

        !#gesv

          !solve linear system

          n       = 2
          nrhs    = 1     !number of columns of b: if many solves several eqs with same A
          a4(1,1) = 1.0
          a4(1,2) = 2.0
          a4(2,1) = 3.0
          a4(2,2) = 4.0
          lda     = 2     !max N,1. Leading Dimenstion A
          b2(1)   = 5.0
          b2(2)   = 11.0
          ldb     = 2     !max 1,N

          !result returned inside of b itself:
          !return status returned on `info`:
          !pivots returned on `pivots`:
          call sgesv( n, nrhs, a4, lda, pivots, b2, ldb, info )
          
          c2(1) = 1.0
          c2(2) = 2.0

          call assert_eqi( info, 0 )
          !assert_eq_vecd(b2,c2,N);

        write(*,*) 'ALL ASSERTS PASSED'

        stop
      end
