import java.util.*
import kotlin.math.abs

const val INF = Int.MAX_VALUE / 2

private class Mat(val a: Array<IntArray>) {
    operator fun times(other: Mat) = Mat(Array(3) { i ->
      IntArray(3) { k ->
          minOf(INF, (0 until 3).minOf { j -> a[i][j] + other.a[j][k] })
      }
    })

    override fun toString(): String {
        return a.joinToString() {it.joinToString()}
    }
}

private fun floyd(a: Array<IntArray>) : Mat {
    for (k in a.indices) {
        for (i in a.indices) {
            for (j in a.indices) {
                a[i][j] = minOf(a[i][j], a[i][k] + a[k][j])
            }
        }
    }
    return Mat(a)
}

private fun Int.has(bit: Int) = ((this shr bit) and 1) != 0



private class Solver(val n: Int) {
    val start = Array(n) { Mat(Array(3) { IntArray(3) { INF } }) }
    class SegmentTree(n: Int) {
        val ID = Mat(Array(3) { i -> IntArray(3) { j -> if (i == j) 0 else INF } })
        companion object {
            fun getLst(n: Int): Int {
                var lst = 2
                while (lst < n) lst *= 2
                return lst
            }
        }

        private val lst = getLst(n)
        private val tree = Array(2 * lst) { ID }

        fun set(pos_:Int, m:Mat) {
            var pos = pos_ + lst
            tree[pos] = m
            while (pos > 1) {
                pos /= 2
                tree[pos] = tree[2*pos] * tree[2*pos+1]
            }
        }

        fun get(v:Int, l:Int, r:Int, L:Int, R:Int) : Mat = when {
            r <= L || R <= l -> ID
            L <= l && r <= R -> tree[v]
            else -> get(2 * v, l, (l + r) / 2, L, R) * get(2 * v + 1, (l + r) / 2, r, L, R)
        }


        fun get(l:Int, r:Int) = get(1, 0, lst, l, r)
    }
    val between = SegmentTree(n - 1)

    fun set(pos:Int, mat:Mat, next:Mat?) {
        start[pos] = mat
        if (pos == n - 1) {
            require(next == null)
        } else {
            between.set(pos, next!!)
        }
    }

    fun query(l: Int, r: Int) : Mat {
        return start[l] * between.get(l, r)
    }
}

private fun solve() {
    val mat1 = Array(8) { mask ->
        val a = Array(3) { i ->
            IntArray(3) { j ->
                when {
                    i == j -> 0
                    abs(i - j) == 1 && mask.has(i) && mask.has(j) -> 1
                    else -> INF
                }
            }
        }
        floyd(a)
    }
    val mat2 = Array(8) { mask1 ->
        Array(8) { mask2 ->
            val a = Array(6) { i ->
                IntArray(6) { j ->
                    if (i / 3 == j / 3) {
                        val mask = if (i / 3 == 0) mask1 else mask2
                        when {
                            i == j -> 0
                            abs(i - j) == 1 && mask.has(i % 3) && mask.has(j % 3) -> 1
                            else -> INF
                        }
                    } else {
                        when {
                            i % 3 == j % 3 && mask1.has(i) && mask2.has(i) -> 1
                            else -> INF
                        }
                    }
                }
            }
            floyd(a)
            Mat(Array(3) { i -> IntArray(3) { j -> a[i][j + 3] } })
        }
    }
    val (n, m) = readInts()
    val a = Array(n) { readInts().map { it - 1 } }
    data class Query(val r1: Int, val c1:Int, val r2: Int, val c2:Int, val l:Int)
    val qs = Array(m) {
        val (r1, c1, r2, c2, l) = readInts().map { it - 1 }
        Query(r1, c1, r2, c2, l)
    }

    val enabled = Array(3) { TreeSet<Int>() }
    val disabled = Array(3) { TreeSet<Int>().apply { addAll(0 until n) }}
    val curMask = IntArray(n) { 0 }

    val s = Solver(n)

    fun enable(x:Int, y:Int) {
        enabled[y].add(x)
        disabled[y].remove(x)
        curMask[x] = curMask[x] or (1 shl y)
        if (x != 0) {
            s.set(x - 1, mat1[curMask[x - 1]], mat2[curMask[x - 1]][curMask[x]])
        }
        s.set(x, mat1[curMask[x]], if (x == n - 1) null else mat2[curMask[x]][curMask[x + 1]])
    }

    for (x in 0 until n) {
        s.set(x, mat1[curMask[x]], if (x == n - 1) null else mat2[curMask[x]][curMask[x + 1]])
    }

    fun query(x1:Int, y1:Int, x2:Int, y2:Int) : Int {

        fun up(x:Int, y:Int) : Pair<Int, Int>? {
            if (y == 1) return null
            return enabled[1].lower(x)?.takeIf {
                val poss = disabled[y].lower(x)
                poss == null || poss < it
            }?.let { it to 1 }
        }

        fun down(x:Int, y:Int) : Pair<Int, Int>? {
            if (y == 1) return null
            return enabled[1].higher(x)?.takeIf {
                val poss = disabled[y].higher(x)
                poss == null || poss > it
            }?.let { it to 1 }
        }

        val cand1 = listOfNotNull(x1 to y1, up(x1, y1), down(x1, y1))
        val cand2 = listOfNotNull(x2 to y2, up(x2, y2), down(x2, y2))

        return cand1.minOf { c1 ->
            cand2.minOf { c2 ->
                if (c1.first < c2.first) {
                    s.query(c1.first, c2.first).a[c1.second][c2.second]
                } else {
                    s.query(c2.first, c1.first).a[c2.second][c1.second]
                } + abs(c1.first - x1) +
                        abs(c1.second - y1) + abs(c2.first - x2) + abs(c2.second - y2)
            }
        }.let { if (it >= INF) 1 else it }
    }



    qs.sortBy { it.l }
    var ans = 1L
    val toEnable = Array(3 * n) { it / 3 to it % 3}
    toEnable.sortBy { a[it.first][it.second] }
    var toEnablePos = 0
    val MOD = 1_000_000_007
    for ((r1, c1, r2, c2, l) in qs) {
        while (toEnable.getOrNull(toEnablePos)?.let { a[it.first][it.second] <= l } == true) {
            enable(toEnable[toEnablePos].first, toEnable[toEnablePos].second)
            toEnablePos++
        }
        ans = (ans * query(r1, c1, r2, c2)) % MOD
    }
    println(ans)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }