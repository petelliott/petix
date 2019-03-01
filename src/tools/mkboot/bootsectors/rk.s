// stage 1 bootloader for rk drives
// TODO: support seperate disks
.set RKDA, 0177412
.set PROG_OFF, 0130000
.set EP_DATA,  0130012
.set DATA_START, 0130020
.set A_TEXT, 0130002
.set A_DATA, 0130004
.set A_BSS,  0130006
.set PROG_STACK, 0160000
.set BLK_SIZE, -256

start:
        MOV $sectors, R2
        MOV $PROG_OFF, R0

sploop:
        MOV (R2)+, R5 // load a sector address
        TST R5
        BEQ eploop

        MOV $0, R4
        DIV $12, R4
        MOV R5, R3 //remainder
        //MOV R4, R1 //quotient
        MUL $16, R4
        ADD R3, R5

        MOV $RKDA, R1
        MOV R5, (R1)         // set disk address
        MOV R0, -(R1)        // set memory address
        MOV $BLK_SIZE, -(R1) // read a block
        MOV $05, -(R1)       // read and go

        ADD $512, R0
notdone:
        TSTB (R1)
        BPL notdone
        BR sploop
eploop:
        // load bss info
        MOV $DATA_START, R0
        ADD @$A_TEXT, R0
        ADD @$A_DATA, R0 //R0 holds address of bss start
        MOV R0, R1
        ADD @$A_BSS, R1  //R1 holds address of bss end
        MOV $0, R2       //R2 holds zero

        CMP R0, R1
        BPL endzerol
zerol:  //zero bss
        MOV R2, (R0)+
        CMP R0, R1
        BMI zerol
endzerol:

        MOV $PROG_STACK, SP
        MOV @$EP_DATA, PC
        HALT

        .=start+0734
diskn:
        .=start+0736
sectors:
        .=start+01000
end:
