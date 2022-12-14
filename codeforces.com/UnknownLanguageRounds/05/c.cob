       IDENTIFICATION DIVISION.
          PROGRAM-ID. SOLUTION.

          DATA DIVISION.
          WORKING-STORAGE SECTION.
          01 OUT-INT  PIC Z(36)9.
          01 OUT-STR  PIC Z(36)X.
          01 IN-INT   PIC X(36).
          01 STR      PIC X(36).
          01 A        PIC 9(36) VALUES ZEROS.
          01 I        PIC 9(26).
          01 J        PIC 9(26).
          01 B        PIC 9(26).
          01 TEMP     PIC 9(26).
          01  C.
            05 NC        USAGE BINARY-CHAR.


          PROCEDURE DIVISION.    
            ACCEPT STR
            ACCEPT IN-INT            
            MOVE IN-INT TO A
            MOVE 0 TO I
            PERFORM VARYING I FROM 36 BY -1 
                UNTIL STR(I:1) NOT = SPACE
            END-PERFORM
            PERFORM UNTIL I = 0
                MOVE STR(I:1) TO C
                ADD NC TO A GIVING B
                SUBTRACT 65 FROM B
                DIVIDE B BY 26 GIVING TEMP REMAINDER B
                ADD 65 TO B
                MOVE B TO NC
                SUBTRACT 1 FROM I GIVING J
                ADD 1 TO I
                STRING STR(1:J)
                       C
                       STR(I:36)
                       INTO STR
                MOVE J TO I
            END-PERFORM
            DISPLAY STR
            STOP RUN.
