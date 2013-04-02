      !mostly focused on differences from c
      !my goal in this is the minimal knowledge for scientific computation
      !i also interested in c interfacing

      !#sources

        !good stanford intro: <http://www.stanford.edu/class/me200c/tutorial_77/>

      !#function declaration
        
        !called **subroutines**

        subroutine incr( i, r, is10 )

          !declaration:
            integer i, is10(10)
            real r
            !real,optional :: iopt

          !execution

            !args passed by reference
            i = i + 1
            r = r + 1.0
            is10(1) = is10(1) + 1
            !iopt = 0.0
            !if( present( iopt ) ) iopt = 1.0

          return
        end

      subroutine assert( b )

        logical b

        if ( .not. b) then
          write(*,*) 'assert failed'
          stop 1
        endif

      end

      !must always have a program:

      program somename

        !#declarations

          !#data types

            logical b, b1, b2
            integer i, i1, i2

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
            parameter ( pi = 1, pr = 1.0 )

          !#array

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

            is2x3(1,1) = 1

            !#string
              
              !cs3 = "01"

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

                call assert( 1 <  2   )
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
30              continue
                !10 is any unique label

              do 40 i = 1, 5, 2
                write(*,*) 'i =', i
40              continue

          !#function call

            i = 1
            r = 1.0
            is10(1) = 1
            call incr( i, r, is10 )
            call assert( i == 2       )
            call assert( r == 2.0     )
            call assert( is10(1) == 2 )

            !compile error:
                !call incr( i, i )
            !type checked

        !#dynamic memory

          !not present?!

        !#stdlib

          !#functions

            !abs
            !min
            !max
            !sqrt
            !sin
            !cos
            !tan
            !atan
            !exp
            !log
  
          !#stdin out

            write (*,*) 'stdout', 1, 1.0, .true.
              !write to stdout

            !read  (*,*) r
              !read from stdin

        !#3rd party

        write(*,*) 'ALL ASSERTS PASSED'

        !#stop

          !ends the program

          !0 exit status:

            stop

          !other exit status:

            !stop 1
      end
