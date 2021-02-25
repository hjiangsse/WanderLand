;;; -----------------util functions------------------
;; genarate a random number in (-seed, seed)
(defun rand-gen (seed)
  (if (equal (random 2) 0)
      (random seed)
      (- (random seed))))

;; generate a random number list
(defun gen-rand-num-lst (seed len)
  (loop for i from 1 to len
	collect (rand-gen seed)))

;; generate cumulative lst
(defun prepare-cum (lst)
  (let ((curcum 0))
    (loop for item in lst
	  collect (setf curcum (+ curcum item)))))

;; get max sublist across some index
(defun get-max-sublst-across-one-index(lst k)
  (if (or (< k 0) (>= k (list-length lst)))
      0
      (+ (let ((sum 0)
	       (lmax 0))
	   (loop for i from (- k 1) downto 0
		 do (progn
		      (setf sum (+ sum (nth i lst)))
		      (setf lmax (max lmax sum))))
	   lmax)
	 (let ((sum 0)
	       (rmax 0))
	   (loop for i from (+ k 1) to (- (list-length lst) 1)
		 do (progn
		      (setf sum (+ sum (nth i lst)))
		      (setf rmax (max rmax sum))))
	   rmax)
	 (nth k lst))))
;;; ---------------different pattern function-------
(defun max-pattern-1 (lst)
  (let ((max-sofar 0)
	(l 0)
	(u (- (list-length lst) 1)))
    (loop for i from l to u
	  do (loop for j from i to u
		   do (let ((subsum 0))
			(loop for k from i to j
			      do (setf subsum (+ subsum (nth k lst))))
			(if (> subsum max-sofar)
			    (setf max-sofar subsum)))))
    max-sofar))

;;v[i,j] = v[i,j-1] + v[j]
(defun max-pattern-2 (lst)
  (let ((max-sofar 0)
	(l 0)
	(u (- (list-length lst) 1)))
    (loop for i from l to u
	  do (let ((v 0))
	       (loop for j from i to u
		     do (progn
			  (setf v (+ v (nth j lst)))
			  (if (> v max-sofar)
			      (setf max-sofar v))))))
    max-sofar))

;;v[i,j] = cum[j] - cum[i - 1]
(defun max-pattern-3 (lst)
  (let ((max-sofar 0)
	(l 0)
	(u (- (list-length lst) 1))
	(cum-lst (prepare-cum lst)))
    (loop for i from l to u
	  do (loop for j from i to u
		   do (let ((subsum 0))
			(if (> i 1)
			    (setf subsum (- (nth j cum-lst)
					    (nth (- i 1) cum-lst)))
			    (setf subsum (nth j cum-lst)))
			(if (> subsum max-sofar)
			    (setf max-sofar subsum)))))
    max-sofar))

;;devide-then-conquer
(defun max-pattern-4 (lst)
  (if (null lst)
      (return-from max-pattern-4 0))
  (if (equal (list-length lst) 1)
      (return-from max-pattern-4  (max 0 (nth 0 lst))))
  (let* ((lower-bound 0)
	 (upper-bound (- (list-length lst) 1))
	 (mid (floor (+ lower-bound upper-bound) 2)))
    (max (max-pattern-4 (subseq lst lower-bound mid))
	 (max-pattern-4 (subseq lst (+ mid 1) upper-bound))
	 (get-max-sublst-across-one-index lst mid))))

;;scanning method
(defun max-pattern-5 (lst)
  (let ((max-sofar 0)
	(max-ending-here 0)
	(l 0)
	(u (- (list-length lst) 1)))
    (loop for i from l to u
	  do (progn
	       (setf max-ending-here
		     (max (+ max-ending-here (nth i lst))
			  0))
	       (setf max-sofar
		     (max max-sofar max-ending-here))))
    max-sofar))
;;;--------------Test Driver-----------------------
(defun test-max-pattern-1 ()
  (let ((lst-len-lst '(1000)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-1 num-lst))))))

(defun test-max-pattern-2 ()
  (let ((lst-len-lst '(1000)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-2 num-lst))))))

(defun test-max-pattern-3 ()
  (let ((lst-len-lst '(1000)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-3 num-lst))))))

(defun test-max-pattern-4 ()
  (let ((lst-len-lst '(1000)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-4 num-lst))))))

(defun test-max-pattern-5 ()
  (let ((lst-len-lst '(1000)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-5 num-lst))))))

(defun main-test ()
  (progn
    (time (test-max-pattern-1))
    (time (test-max-pattern-2))
    (time (test-max-pattern-3))
    (time (test-max-pattern-4))
    (time (test-max-pattern-5))))




