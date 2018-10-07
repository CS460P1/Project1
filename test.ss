; Card program in Scheme
(define (nextrank rank)    ; this function just facilitates dealing
  (cond ((eq? rank 'K) 'Q)
	(define (nextrank rank)    ; this function just facilitates dealing
  (cond ((eq? rank 'K) 'Q)
        ((eq? rank 'Q) 'J)
        ((eq? rank 'J) 'T)
        ((eq? rank 'T) '9)
        ((eq? rank '9) '8)
        ((eq? rank '8) '7)
        ((eq? rank '7) '6)
        ((eq? rank '6) '5)
        ((eq? rank '5) '4)
        ((eq? rank '4) '3)
        ((eq? rank '3) '2)
        ((eq? rank '2) 'A)
        ((eq? rank 'A) 'K)
  )
)
	; Card program in Scheme
;
;
; each card is represented as a list.  For example,
; the queen of spades is (Q S)

; The hand itself is stored in 13 'stacks', from the
; Ace stack to King.  To make this searchable, the
; name of the stack is stored with the stack.  For
; example (5 (K D) (2 C)) means that the stack associated
; with 5 has a K of diamonds on top of a two of clubs.
;
; So, an entire hand might look something like:
; ((A (J C) (2 H) (3 S)(4 D)) (2 (5 D) (Q D) (7 H) (2 C)) ... (K ...) )
;


(define (clockpatience cards)
   (let ((hand (deal cards 'K)))
     (play (topcard 'K hand) 'K  hand 1)
   )
)

(define (initialhand)
'( (A)(2)(3)(4)(5)(6)(7)(8)(9)(T)(J)(Q)(K))
)

(define (sample)
'( (T S)(Q C)(8 S)(8 D)(Q H)(2 D)(3 H)(K H)(9 H)(2 H)(T H)(K S)(K C)
(9 D)(J H)(7 H)(J D)(2 S)(Q S)(T D)(2 C)(4 H)(5 H)(A D)(4 D)(5 D)
(6 D)(4 S)(9 S)(5 S)(7 S)(J S)(8 H)(3 D)(8 C)(3 S)(4 C)(6 S)(9 C)
(A S)(7 C)(A H)(6 H)(K D)(J C)(7 D)(A C)(5 C)(T C)(Q D)(6 C)(3 C))
)


(define (deal cards rank)
  (cond ((null? cards) (initialhand) )
        (else (addstack rank (car cards) (deal (cdr cards) (nextrank rank))))
  )
)
