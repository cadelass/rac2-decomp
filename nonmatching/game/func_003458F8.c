/*
 * func_003458F8: matches USA v1.01 at every place (was src/game/00345358-g8.c) but not PAL or USA v2.00 (tools/build.py --strict --version pal/us2: instruction at +0x34 differs); left out of #368. Fix it for every release (docs/VERSIONS.md) before it goes back into src/.
 */
void func_003458F8(SelectionOwner *owner, int buttons)
{
    if (buttons & 0x1000) {
        int row;
        func_002E5E58(3, 0, 0);
        row = owner->row - 1;
        owner->row = row;
        if (row < 0) {
            owner->row = 0;
            owner->state = 1;
        }
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        if (owner->row == 0) {
            if (owner->column == 0) {
                owner->column = 1;
                owner->row = 1;
            } else
                owner->row = 1;
        } else if (owner->row == 1) {
            owner->state = 3;
            owner->row = 0;
            owner->column--;
        }
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        --owner->column;
        if (owner->row == 0)
            owner->column = owner->column < 0 ? 2 : owner->column;
        else
            owner->column = owner->column < 1 ? 2 : owner->column;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++owner->column;
        if (owner->row == 0)
            owner->column = owner->column > 2 ? 0 : owner->column;
        else
            owner->column = owner->column > 2 ? 1 : owner->column;
    } else if (buttons & 0x40) {
        int id = D_00259CE0[owner->column + owner->row * 3].v[3];
        if (id && D_001A7AF8[id]) {
            func_002E5E58(4, 0, 0);
            D_001F2880[0] = id;
            owner->selected = id;
        } else
            func_002E5E58(5, 0, 0);
    }
    {
        int id = D_00259CE0[owner->column + owner->row * 3].v[3];
        owner->selected = id;
        if (id && D_001A7AF8[id])
            D_001ADB10 = ((SelectionMaterial *)(D_00239BA0 + D_00139568[id] * 0xE0))->material;
    }
}
