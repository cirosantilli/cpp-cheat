        subroutine s( i, r, d, is2x2 )

          integer i
          integer is2x2(2,2)
          real r
          real(8) d

          i = i + 1
          r = r + 1.0
          d = d + 1.0d0

          is2x2(1,1) = 0
          is2x2(1,2) = 1
          is2x2(2,1) = 2
          is2x2(2,2) = 3

          write(*,*) "s(int)", i, r, d, is2x2

          return
        end

        integer function f( i )

          integer i
          i = i + 1
          write(*,*) "f(int)", i
          f = i

          return
        end
