      !standard fortran interface

      !my function descriptions will be here,
      !other lapack cheats show only different interfaces.

      subroutine assert_eqi( a, b )

        integer a, b

        if ( a /= b) then
          write(*,*) 'assert_eqi failed'
          write(*,*) 'a', a
          write(*,*) 'b', b
          stop 1
        endif

      end

      subroutine assert_eqr( x, y, err )

        real x, y, err

        if ( abs( x - y ) >= err ) then
          write(*,*) 'assert_eqr failed'
          write(*,*) 'y', x
          write(*,*) 'x', y
          write(*,*) 'err', err
          stop 1
        endif

      end

      !euclidean distance |x-y|_2
      function dist2( n, x, y )

        integer n
        real x(n), y(n)

        call saxpy( 2, -1.0, x, 1, y, 1 )
        dist2 = snrm2( n, y, 1 )
        return

      end

      !assert |x-y|_2 <= err
      subroutine assert_eqvr2( n, x, y, err )

        integer n
        real x(n), y(n), err
        real dist2

        if ( dist2( n, x, y ) >= err ) then
          write(*,*) 'assert_eq_vr_norm2 failed'
          write(*,*) 'x', x
          write(*,*) 'y', y
          write(*,*) 'err', err
          stop 1
        endif

      end

      program main

        integer n, nrhs, lda, ldb, info, pivots(2)
        real a2x2(2,2), b2(2), c2(2), x2(2), x4(4), y2(2), err

        err = 10e-6

        !#blas

          !#common arguments

          !most commands start with the array dimension as argument

            !ex:

              x4(1) = 1.0
              x4(2) = 1.0
              x4(3) = 1.0
              x4(4) = 1.0
              call assert_eqr( snrm2(4, x4, 1), 2.0, err )
              !                      ^                    
              !                      array length

          !#indx

            !argument present on lots of the level 1 ops.

            !takes every nth value only.

            !array must be indx times larger

            !TODO make this work

            x4(1) = 1.0
            x4(2) = 1.0
            x4(3) = 1.0
            x4(4) = 1.0
            !call assert_eqr( snrm2(4, x4, 2), sqrt(2.0), err )
            !                             ^             
            !                             indx     

          !#nrm2

            !euclidean norm 2

            x2(1) = 1.0
            x2(2) = -2.0
            call assert_eqr( snrm2(2, x2, 1), sqrt(5.0), err )

          !#axpy

            !y = \alpha * x + y

            !x
            x2(1) = 1.0
            x2(2) = -2.0

            !y
            y2(1) = 3.0
            y2(2) = -4.0

            call saxpy(2, 2.0, x2, 1, y2, 1)
            !             1        2      3 
            !1: \alpha
            !2: incx
            !3: incy
            call assert_eqr( y2(1), 5.0,  err )
            call assert_eqr( y2(2), -8.0, err )

          !#scal

            !x = \alpha x

            x2(1) = 1.0
            x2(2) = -2.0
            call sscal( 2, 2.0, x2, 1 )

            y2(1) = 2.0
            y2(2) = -4.0
            call assert_eqvr2( 2, x2, y2, err )

          !#i.amax

            !index of largest absolute value in array

            x4(1) = 1.0
            x4(2) = -1.0
            x4(3) = -2.0
            x4(4) = 0.0
            call assert_eqi( isamax(4, x4, 1), 3 )

        !#lapack

          !#gesv

            !solve general linear system

            n         = 2
            nrhs      = 1     !number of columns of b: if many solves several eqs with same A
            a2x2(1,1) = 1.0
            a2x2(1,2) = 2.0
            a2x2(2,1) = 3.0
            a2x2(2,2) = 4.0
            lda       = 2     !max N,1. Leading Dimenstion A
            b2(1)     = 5.0
            b2(2)     = 11.0
            ldb       = 2     !max 1,N

            !result returned inside of b itself:
            !return status returned on `info`:
            !pivots returned on `pivots`:
            call sgesv( n, nrhs, a2x2, lda, pivots, b2, ldb, info )

            c2(1) = 1.0
            c2(2) = 2.0
            call assert_eqi( info, 0 )
            call assert_eqvr2( 2, b2, c2, err );

          !#

        stop
      end
