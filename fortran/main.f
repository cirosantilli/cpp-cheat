      !mostly focused on differences from C
      !my goal in this is the minimal knowledge for scientific computation
      !i also interested in c interfacing

      !#sources

        !good stanford intro: <http://www.stanford.edu/class/me200c/tutorial_77/>

      !#function

        !there are two types: functions and **subr_incroutines**

        integer function func_incr( i )

          integer i

          !func args are passed by value
          i = 1

          !there can be a return value:

            func_incr = i + 1

          return

        end

        subroutine subr_incr( i, r, n, is )

          !subr_incroutine args are passed by reference

          !declaration:
            integer i, n, is(n)
            real r
            !real,optional :: iopt

          !execution

            i = i + 1
            r = r + 1.0
            is(1) = is(1) + 1
            !iopt = 0.0
            !if( present( iopt ) ) iopt = 1.0
            call assert( size(is) == n )

          !subr_incroutine cannot return a value:

            !return 1

          return

        end

      subroutine assert( b )

        logical b

        if ( .not. b) then
          write(*,*) 'ASSERT FAILED'
          stop 1
        endif

      end

      !must always have a program:

      program somename

        !#declarations

          !#data types

            logical b, b1, b2
            integer i, i1, i2

            !for file io
              character(256) :: arg
              integer u
            !looks like a linux file handle

            !you need to declare the ype of functions again:
              integer func_incr

            !integer i = 1
              !ERROR
              !cannot init on declare
              !must use param instead

            !integer I
              !ERROR
              !vars are case insensitive

            real r, r1, r2, r3
            real(8) d, d2

            !double precision:
            double precision d3, d4
            character c, c1, c2

            !constants:
            integer parami
            real paramr
            parameter ( parami = 3, paramr = 1.0 )

          !#array

            integer is2(2)
            integer is10(10)

            integer isrm55(-5:5)
            !is Range Minus 5 to 5
            !BAD
            !confusing!!

            integer is11
            dimension is11(11)
            !BAD
            !bad golfing
            !hard to see is3 is an array

            !#multidimensional

              integer is2x3(2,3)
              integer is2x2(2,2)

            character cs3(3)

          !#whitespace
            !- multiple whitespace is ignored
            !- all whitespace is treated equally
            !- indentation is not forced
            !- first five characters of each line are reserved for labels
              !only then can you write statements
            !- non-comment lines have a maxium length!
!^^^^
!!!!!

          !#comments
            !!: bang anywhere or first char
            !c: first char

        !#execution

          !compile error
          !can only declare before first execution statement:

            i = 2
            !real r2

          !#constants

            b = .TRUE.
            b = .true.
            b = .FALSE.

            i = 1

            r = 2.0
            r = 2.0e1

            !bad: r is a single precision variable
                r = 2.0d1

            !compile error:
                !r = 2.
            !needs `2.0`

            !d is for explcit double precision
                d1 = 2.0
                d3 = 2.0d0

            c = 'a'
            c = "a"
            !c = "\n"
            c = "'"
            c = ''''
            c = """"

            !compile error:
              !parami = 2

          !#array

            is10(1) = 1
            is10(10) = 1

            !is10(0) = 1
              !compile time error
              !starts at 1!!

            !is10(11) = 1
              !compile time error
              !TODO confirm: at compile time because no dynamic memory

            isrm55(-5) = 1
            isrm55(5) = 1

            !#multidimensional

              is2x3(1,3) = 1

              !physical memory column major:

                is2x2(1,1) = 1
                is2x2(1,2) = 2
                is2x2(2,1) = 3
                is2x2(2,2) = 4
                write(*,*) is2x2
                  !outputs 1 3 2 4

            !#string

              !cs3 = "01"

            !size function
            !f90
              call assert( size(is2) == 2 )

          !#logic

            b = .true. .AND. .false.
            b = .true. .and. .false.
            b = .true. .or. .false.
            b = .not. .true.

          !#arithmetic

            !#arithmetic

              i = 2**3
                !exponentiation

              !#compare

                call assert( 1 <  2     )
                call assert( 1 .lt. 2   )
                call assert( 1 ==   1   )
                call assert( 1 .eq. 1   )
                call assert( 1 /=   2   )
                call assert( 1 .ne. 2   )

          !#branch

            !#if

              !#single line

                if ( .true. ) r = 1.0

              !#multiline

                if ( .true. ) then
                  r = 1.0
                elseif ( .true. ) then
                  r = 2.0
                else
                  r = 3.0
                endif

            !#label

              !labels must be integers
              !               on five first chars of line
              !must be part of some statement
!10
!20
              !convention only: cosecutive multiples of ten
!11

            !#for

              do 30 i = 1, 5
                write(*,*) 'i =', i
30            continue
                !10 is any unique label

              do 40 i = 1, 5, 2
                write(*,*) 'i =', i
40            continue

          !#function call

            !#function

              !call assert( func_incr(1) == 2 )
              i = 1
              i2 = func_incr( i )
              call assert( i  == 1 )
              call assert( i2 == 2 )

            !#subroutine

              i = 1
              r = 1.0
              is10(1) = 1
              call subr_incr( i, r, 10, is10 )
              call assert( i == 2       )
              call assert( r == 2.0     )
              call assert( is10(1) == 2 )

              !compile error:
                  !call subr_incr( i, i )
              !type checked

        !#dynamic memory

          !not present?!

        !#stdlib

          !unlike c, in fortran you don't need to include files,
          !you just try to link to them directly

          !therefore, the compiler won't be able to tell if the
          !function call signatures are ok.

          !#intrinsics

            !buil-in functions

            !#math

              is2(1) = -1
              is2(2) = -2
              call assert( abs(-1)   == 1   )
              call assert( abs(-1.0) == 1.0 )
              write (*,*) abs(is2)

              !min
              !max
              !sqrt
              !sin
              !cos
              !tan
              !atan
              !exp
              !log

            call get_command_argument(0, arg)
            write(*,*) arg

          !#IO

            !#stdout

              is2(1) = 1
              is2(2) = 2
              write(*,*) 'stdout', 1, 1.0, .true., is2

            !#stdin

              !read  (*,*) r

            !#file IO

              !TODO

              is2(1) = 1
              is2(2) = 2
              !open( u, file='tmp.tmp' )
              !write( u, * ) 'file', 1, 1.0, .true., is2
              !close( u )

        !#stop

          !ends the program

          !0 exit status:

            stop

          !other exit status:

            !stop 1
      end
