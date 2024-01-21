$fa = 0.01;
$fn = 80;
height_tube = 12 + 8;
tube_id = 19.1;
tube_wall_thinkness = 1.6;
dispo_length_extra = 10;
dispo_length = dispo_length_extra + tube_id / 2 + tube_wall_thinkness;
tube_recess = 4.5;

difference()
{
    union()
    {
        cylinder(h = height_tube, d = tube_id + tube_wall_thinkness * 2);
        // translate([-(tube_id+tube_wall_thinkness*2)/2,-tube_wall_thinkness])
        // cube([tube_id+tube_wall_thinkness*2,dispo_length,height_tube ]);
    }
    translate([ 0, 0, -tube_wall_thinkness ]) cylinder(h = height_tube, d = tube_id);
    translate([ -tube_id / 2, 0, tube_recess ]) cube([ tube_id, dispo_length, height_tube - tube_recess ]);
    translate([ -1 / 2, tube_id / 2 - 0.1 / 2, -0.01 / 2 ]) cube([ 1, tube_wall_thinkness + 0.1, tube_recess + 0.01 ]);
}

difference()
{
    union()
    {
        // cylinder(h = height_tube, d = tube_id+tube_wall_thinkness*2);
        translate([ -(tube_id + tube_wall_thinkness * 2) / 2, -tube_wall_thinkness ])
            cube([ tube_id + tube_wall_thinkness * 2, dispo_length, height_tube ]);
    }
    translate([ 0, 0, -tube_wall_thinkness ]) cylinder(h = height_tube, d = tube_id);
    translate([ -tube_id / 2, 0, -tube_wall_thinkness ]) cube([ tube_id, dispo_length, height_tube ]);
}
