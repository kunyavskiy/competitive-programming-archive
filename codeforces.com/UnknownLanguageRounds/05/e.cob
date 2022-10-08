       IDENTIFICATION DIVISION.
          PROGRAM-ID. SOLUTION.

          DATA DIVISION.
          WORKING-STORAGE SECTION.
          01 IN-INT   PIC X(36).
          01 SHIFT    PIC 9(36).
          01 TEMP     PIC 9(36).
          01 RES      PIC 9(36).
          01 N        PIC 9(36).
          01 I        PIC 9(36).
          01 J        PIC 9(36).
          01 DX       PIC S9(36).
          01 DY       PIC S9(36).
          01 VB-TABLE.
              02 X     PIC S9(36) OCCURS 50.
              02 Y     PIC S9(36) OCCURS 50.



          PROCEDURE DIVISION.    
            ACCEPT IN-INT
            MOVE IN-INT TO N
            MOVE 1 TO I
            PERFORM UNTIL I > N
               ACCEPT IN-INT
               MOVE IN-INT TO X(I)
               ACCEPT IN-INT
               MOVE IN-INT TO Y(I)
               ADD 1 TO I
            END-PERFORM

            MOVE 1 TO I
            MOVE 0 TO RES
            PERFORM UNTIL I > N
                MOVE I TO J
                ADD 1 TO J
                PERFORM UNTIL J > N
                    SUBTRACT X(I) FROM X(J) GIVING DX
                    SUBTRACT Y(I) FROM Y(J) GIVING DY
                    MULTIPLY DX BY DX
                    MULTIPLY DY BY DY
                    ADD DX TO DY GIVING TEMP
                    display temp
                    IF TEMP > RES
                       MOVE TEMP TO RES
                    END-IF
                    ADD 1 TO J
                END-PERFORM
                ADD 1 TO I
            END-PERFORM

            DISPLAY FUNCTION SQRT (RES)
            STOP RUN.
