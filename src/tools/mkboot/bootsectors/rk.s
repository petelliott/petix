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
        MOV $pages, R2

sploop:
        MOV @(R2)+, R3 // load a sector address
        TST R3
        BEQ eploop

        MOV $RKDA, R1
        MOV R3, (R1)         // set disk address
        MOV $PROG_OFF, -(R1) // set memory address
        MOV $BLK_SIZE, -(R1) // read a block
        MOV $05, -(R1)       // read and go
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

diskn:  .=start+0734
pages:  .=start+0736
end:    .=start+01000
