/* Exact in USA v1.01, not landable as one definition: -O2 -G8 -ffunction-sections, own unit
 * (e.g. src/game/00345358-pad-g8.c). check.py: 536/536 bytes, us 28/28 places; pal 0/28, us2 0/28.
 * PAL and v2.00 retail read the owner's fields at 0x4FC/0x500/0x504/0x508 instead of
 * 0x48C/0x490/0x494/0x498: the structure grew by 0x70, every other difference is an address.
 * Landing it needs the releases' own copies (not_carried.tsv, src/pal, src/us2 with their
 * offset, as upstream 85f87be8 did), not a different wording of this C.
 * What closed the v1.01 gap: D_001A7AF8 is a two-word macro address (section .sdata), so it
 * cannot fill the zero-id branch's slot and reorg takes a0=5 from the target; `column` is one
 * variable over three blocks, so global allocation keeps it off $v0 and it gets $v1; `next` is
 * local to the 0x1000 block, which orders that block's three quantities -1, next, 3.
 */
typedef struct { short v[5]; } SelectionEntry;
typedef struct { char pad[0x48c]; int column, row, selected, state; } SelectionOwner;
typedef struct { char pad[6]; short material; char tail[216]; } MaterialRecord;
typedef struct { char pad[0x44]; int selected; } EquipmentState;

extern void func_002E5E58(int, int, int);
extern unsigned char D_001A7AF8[] __attribute__((section(".sdata")));
extern unsigned char D_00139568[];
extern MaterialRecord D_00239BA0[];
extern int D_001ADB10 __attribute__((sda));
extern SelectionEntry D_001AA898[];
extern EquipmentState D_001F2840;

#define MATERIAL(id) ((MaterialRecord *)(D_00139568[id]*224 + (char *)D_00239BA0))->material

void func_00345D58(SelectionOwner *o, int buttons)
{
    int id, column;

    if (buttons & 0x1000) {
        int next;

        func_002E5E58(3, 0, 0);
        column = o->column;
        next = column - 1;
        o->row = 0;
        o->state = 3;
        if (next < 0)
            next = 0;
        o->column = next;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        o->row = 0;
        o->state = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        column = o->column;
        column--;
        o->column = column;
        if (column < 0)
            o->column = 2;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        column = o->column;
        column++;
        o->column = column;
        if (column >= 3)
            o->column = 0;
    } else if (buttons & 0x40) {
        id = D_001AA898[o->column].v[3];
        if (id != 0 && D_001A7AF8[id] != 0) {
            func_002E5E58(4, 0, 0);
            D_001ADB10 = MATERIAL(o->selected);
            if (D_001F2840.selected == id)
                D_001F2840.selected = 0;
            else
                D_001F2840.selected = id;
        } else {
            func_002E5E58(5, 0, 0);
        }
    }
    {
        int selected = D_001AA898[o->column].v[3];
        o->selected = selected;
        if (selected != 0 && D_001A7AF8[selected] != 0)
            D_001ADB10 = MATERIAL(selected);
    }
}
