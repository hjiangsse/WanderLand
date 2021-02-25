;;; -----------------util functions------------------
;; genarate a random number in (-seed, seed)
(defun rand-gen (seed)
  (if (equal (random 2) 0)
      (random seed)
      (- (random seed))))

;; geneate a random number list
(defun gen-rand-num-lst (seed len)
  (loop for i from 1 to len
	collect (rand-gen seed)))

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

;;;--------------Test Driver-----------------------
(defun test-max-pattern-1 ()
  (let ((lst-len-lst '(1 10 100 200 300)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-1 num-lst))))))

(defun test-max-pattern-2 ()
  (let ((lst-len-lst '(1 10 100 200 300)))
    (loop for len in lst-len-lst
	  do (let ((num-lst (gen-rand-num-lst 100 len)))
	       (print (max-pattern-2 num-lst))))))

