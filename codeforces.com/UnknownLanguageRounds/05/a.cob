       IDENTIFICATION DIVISION.
          PROGRAM-ID. SOLUTION.

          DATA DIVISION.
          WORKING-STORAGE SECTION.
          01 A        PIC 9(36)   VALUE ZEROES.
          01 B        PIC 9(36)   VALUE ZEROES.
          01 C        PIC 9(36)   VALUE ZEROES.
          01 D        PIC 9(36).
          01 TEMP     PIC 9(36).
          01 OUT      PIC Z(36)9.
          77 STR      PIC X(36).

          PROCEDURE DIVISION.
            ACCEPT STR
            MOVE STR TO A
            ADD 1 to C
            PERFORM UNTIL A = 0 
                MOVE 0 to D
                DIVIDE A BY 2 GIVING TEMP REMAINDER D
                MOVE TEMP TO A
                MULTIPLY C BY D
                MULTIPLY 10 by C
                ADD D TO B
            END-PERFORM

            MOVE B TO OUT
            DISPLAY OUT
            STOP RUN.
