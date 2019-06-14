/* this is a test sample  // * / */
/* true part */
winterfell(ned).
winterfell(sansa).
winterfell(arya).
father(ned,sansa).
bastard(jon_Snow).
lannister(cercei).
lannister(tyrion).
lannister(jaime).
mother(cercei,joffrey).
kill(joffrey,ned).
halfman(tyrion).
imp(X) :- halfman(X),lannister(X).
family(cercei,tyrion,jaime).
dead2together(cercei,jaime).
targaryen(jon_Snow).
targaryen( daenerys ).
friend(jon_Snow, sam).
story_end(gameofthrones) :- kill(jon_Snow,daenerys).



