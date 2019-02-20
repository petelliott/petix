// stage 1 bootloader for rk drives
.set FILE, 01 // cylinder 0, surface 0, sector 1
.set RKDA, 0177412
.set PROG_OFF, 0130000
.set EP_DATA,  0130012
.set PROG_STACK, 0160000
.set WORD_COUNT, -1024 //number of words for second stage boot loader

start:
        //MOV $063, @$0177566
        MOV $RKDA, R1
        MOV $FILE, (R1)        // set disk address
        MOV $PROG_OFF, -(R1)   // set memory address
        MOV $WORD_COUNT, -(R1) // set word count
        MOV $05, -(R1)         // read and go
notdone:
        TSTB (R1)
        BPL notdone
        MOV $PROG_STACK, SP
        MOV @$EP_DATA, PC
        HALT

end:    .=start+01000
