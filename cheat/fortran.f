c fotran cheatsheet

c mostly focused on differences from c
c my goal in this is the minimal knowledge for scientific computation
c i also interested in c interfacing

c #sources

c good stanford intro: <http://www.stanford.edu/class/me200c/tutorial_77/>

      !#function declaration
        
        !called **subroutines**

        subroutine incr (i, r)

          !args passed by reference

          !declaration
            integer i
            real r

          !execution
            i = i + 1
            r = r + 1.0

          return
        end

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
          character c, c1, c2

          parameter ( pi = 1, pr = 1.0 )
            !constants

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
  
          !real r2
            !ERROR
            !can only declare at beginning!

          !#whitespace
            !is ignored
            !only newlines are important
            !indentation is not obliged
            !first five characters are reserved for labels
            !only then can you write statements
!^^^^
!!!!!

          !#comments
            !!: bang anywhere or first char
            !c: first char

        !#execution

          !#constants

            b = .TRUE.
            b = .true.
            b = .FALSE.

            i = 1

            r = 2.0
            r = 2.0e1
            !r = 2.
              !#error

            c = 'a'
            c = "a"
            !c = "\n"
            c = "'"
            c = ''''
            c = """"

          !#array

            is10(1) = 1
            is10(10) = 1

            !is(0) = 1
              !ERROR
              !starts at 1!!

            !is(11) = 1
              !ERROR
              !bound checking is done
              !TODO confirm: (at compile time because no dynamic memory)

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

                b = 1 < 2
                b = 1 .lt. 2
                b = 1 == 2
                b = 1 .eq. 2
                b = 1 /= 2
                b = 1 .ne. 2

              
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
            call incr( i, r )
            write(*,*) i, r

          !#dynamic memory

            !not present?!

          !#predefined functions

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
  
          !#stdin/out

            write (*,*) 'stdout', 1, 1.0, .true.
              !write to stdout

            !read  (*,*) r
              !read from stdin

        stop
      end
