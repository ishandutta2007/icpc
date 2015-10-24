main = interact $ show . f
    where
        f sx = min (g sx '1') (g sx '0')
            where
                g [] c = 0
                g (x:sx) c = g sx c + (if x == c then 1 else 0)