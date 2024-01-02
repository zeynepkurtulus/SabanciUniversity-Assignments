(define twoOperatorCalculator (lambda (lst)
		(if (null? (cdr lst)) ;checks if the list lst has only one element (cdr extracts the elements starting from index)
			(car lst) ; if so return the first and only element
			; at the point the	list has more than one element  
			(if (eq? '+ (car (cdr lst))) ; check if the second element is '+'
				; (car lst) = first operand (car (cdr (cdr lst))) = second operand and + performs the addition (cdddr lst) extracts the sublist starting from the 4th element recursively calls the func.  
				(twoOperatorCalculator (cons (+ (car lst) (car (cdr (cdr lst))) ) (cdddr lst) ) )
				(if (eq? '- (car (cdr lst)))
					(twoOperatorCalculator (cons (- (car lst) (car (cdr (cdr lst))) ) (cdddr lst)  ) )
					
)))))

(define fourOperatorCalculator (lambda (lst)
	(if (null? (cdr lst)) ;checks if the list lst has only one element
		lst ; if it has one element return it 
		(if (eq? '* (car (cdr lst))) ; checks if the second element i.e the operator is *
			; if it is a multiplication extract the first operant and the third operant and perform *, then cdddr gives the sublist starting from the 4th element and performs recursion on th erest of the list 
			(fourOperatorCalculator (cons (* (car lst) (car (cdr (cdr lst))) ) (cdddr lst) ) ) 					
			; if the second symbol i.e. the operant is / 
			 (if (eq? '/ (car (cdr lst)))
					; take the first and third element and perform division, perform recursion on the remaining list 
                                        (fourOperatorCalculator (cons (/ (car lst) (car (cdr (cdr lst))) ) (cdddr lst) ) )
					;if the second element i.e. the first operator is not * or / then we call the function on the remaining list to detect whether there exists * or / in the list 
					(cons (car lst) (fourOperatorCalculator (cdr lst) ) )
)))))


(define calculatorNested (lambda(lst)
			   (cond
			     ((null? lst) #f)
			     ((and (eq? (length lst) 1) (number? (car lst))) (list (car lst)))
			     ((and (list? (car lst)) (not (null? (cdr lst)))) (cons (twoOperatorCalculator (fourOperatorCalculator (calculatorNested (car lst)))) (cons (cadr lst) (calculatorNested (cddr lst)))))
			     ((and (list? (car lst)) (null? (cdr lst))) (list (twoOperatorCalculator (fourOperatorCalculator (calculatorNested (car lst))))))
			     ((and (not (list? (car lst))) (not (null? (cdr lst)))) (cons (car lst) (cons (cadr lst) (calculatorNested (cddr lst)))))
			     (else (list (car lst))))))

(define checkOperators (lambda (lst)
	(cond
		((null? lst) #f) ; empth list is not allowed
		((and (number? lst) (not (list? lst)) ) #f) ; single numbers i.e. numbers without a list not allowed
                ((and (symbol? lst) (not (list? lst)) ) #f) ; symbols are not allowed
		((list? (car lst)) ; if the first element is a list 
		(if (null? (cdr lst))  
			(checkOperators(car lst)) ; check for the op
			(and (checkOperators(cdr lst)) (checkOperators(car lst)))))
		((number? (car lst)) 
			(if (not(null? (cdr lst)) )
				(if (not (number? (cadr lst)))
					(checkOperators (cdr lst))
					#f)
				#t))
		((or  (eq? '/ (car lst)) (eq? '- (car lst)) (eq? '+ (car lst))(eq? '* (car lst)))
			(if (not (null? (cdr lst)))
				(checkOperators (cdr lst))
				#f))
		((not (and (not (number? (car lst))) (or (eq? '* (car lst)) (eq? '/ (car lst)) (eq? '+ (car lst)) (eq? '- (car lst))) ) ) #f)
		(else #t)
)))

(define calculator (lambda (lst)
	(if (checkOperators lst)
		(twoOperatorCalculator (fourOperatorCalculator(calculatorNested lst)))
		#f
)))
