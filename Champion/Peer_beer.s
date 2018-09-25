.name		"Peer_beer"
.comment	"oh, and don't forget about snacks"

beer:
	ld		%1, r2
	st		r1, r3
	fork	%:beer2
	st		r3, 6
	live	%42
	fork	%:snack
	st		r3, 6
	live	%42

beer2:
	st		r3, 6
	live	%42
	fork	%:snack2
	ld		%0, r4
	zjmp	%-1500

snack:
	st		r3, 6
	live	%42
	fork	%:snack2
	ld		%0, r4
	zjmp	%-400

snack2:
	sti		r2, %398, r2
	sti		r1, %396, r2
	sti		r2, %398, r2
	sti		r1, %396, r2
	sti		r2, %-398, r2
	sti		r1, %-400, r2
	fork	%:beer
	sti		r2, %398, r2
	sti		r1, %396, r2
	sti		r2, %398, r2
	sti		r1, %396, r2
	sti		r2, %-398, r2
	sti		r1, %-400, r2
	zjmp	%-1500

segfault:

ld %115,r3
aff r3
ld %101,r3
aff r3
ld %103,r3
aff r3
ld %109,r3
aff r3
ld %101,r3
aff r3
ld %110,r3
aff r3
ld %116,r3
aff r3
ld %97,r3
aff r3
ld %116,r3
aff r3
ld %105,r3
aff r3
ld %111,r3
aff r3
ld %110,r3
aff r3
ld %110,r3
aff r3
ld %32,r3
aff r3
ld %102,r3
aff r3
ld %97,r3
aff r3
ld %117,r3
aff r3
ld %108,r3
aff r3
ld %116,r3
aff r3