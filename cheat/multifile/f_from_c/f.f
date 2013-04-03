        integer function f( i )
          integer i
          i = i + 1
          write(*,*) "f(int)", i
          f = i
          return
        end

        subroutine s( i )
          integer i
          i = i + 1
          write(*,*) "s(int)", i
          return
        end
