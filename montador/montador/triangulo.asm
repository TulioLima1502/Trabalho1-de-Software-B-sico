	TRIANGULO: EQU 1
SECTION DATA
	B:		SPACE
	H:		SPACE
	R:		SPACE
	DOIS:	CONST		2
SECTION TEXT
	ISSO:		MACRO
		INPUT		B
		INPUT		H
		LOAD		B
	ENDMACRO
		MULT		H
		IF TRIANGULO
				TESTE: MACRO
		DIV		DOIS
		ENDMACRO
		ISSO
		STORE		R
		OUTPUT	R
		STOP


		

