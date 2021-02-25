(defun bi-search (lst l u d)
  (if (>= l u)
      -1
      (let* ((m (floor (+ l u) 2))
             (mid-elem (nth m lst)))
	(if (equal mid-elem d)
            m
            (if (< mid-elem d)
		(bi-search lst (+ m 1) u d)
		(bi-search lst l (- m 1) d))))))

(defun is-sorted (lst l u)
  (if (>= l u)
      t
      (
  
