private class BIT(val n: Int) {
    private val x = IntArray(n)

    fun add(pos:Int, value: Int) {
        var ppos = pos
        while (ppos < n) {
            x[ppos] += value
            ppos = ppos or (ppos + 1)
        }
    }

    fun get(pos: Int): Int {
        var ans: Int = 0
        var ppos = pos
        while (ppos != -1) {
            ans += x[ppos]
            ppos = (ppos and (ppos + 1)) - 1
        }
        return ans
    }
    fun get(l:Int, r:Int) = get(r - 1) - get(l - 1)
}

private sealed class Event(val ty:Int) {
    abstract val x: Int

    data class Query(override val x: Int, val ly: Int, val ry: Int, val coef: Int) : Event(0)
    data class Update(override val x: Int, val y: Int) : Event(1)
}


private fun count(r: Int, c: Int, ids: List<IntArray>, lim: Int): Long {
    var ans = 0L
    for (i in 0 until r) {
        for (j in 0 until c) {
            val mi = maxOf(0, i - lim)
            val Mi = minOf(r, i + lim+1)
            val mj = maxOf(0, j - lim)
            val Mj = minOf(c, j + lim+1)
            ans += (Mi - mi) * (Mj - mj)
        }
    }
    val bit = BIT(c)
    for (col in ids) {
        val qs = buildList {
            for (it in col.indices) {
                val x = it / c
                val y = it % c
                add(Event.Update(x, y))
                add(Event.Query(maxOf(x - lim, -1), maxOf(y - lim, 0), minOf(y + lim + 1, c), -1))
                add(Event.Query(maxOf(x + lim + 1, c), maxOf(y - lim, 0), minOf(y + lim + 1, c), -1))
            }
            sortBy { 2 * it.x + it.ty }
        }
        for (it in qs) {
            when (it) {
                is Event.Update -> bit.add(it.y, 1)
                is Event.Query -> ans += it.coef * bit.get(it.ly, it.ry)
            }
        }
        for (it in qs) {
            when (it) {
                is Event.Update -> bit.add(it.y, -1)
                is Event.Query -> {}
            }
        }
    }
    return ans
}

private fun solve() {
    val (r_, c_, k) = readLongs()
    val r = r_.toInt()
    val c = c_.toInt()
    val a = List(r) { readInts().toIntArray() }
    val ids = (0 until r * c).groupBy { a[it / c][it % c] }.values.map { it.toIntArray() }
    var lf = 0
    var rg = maxOf(r, c) + 1
    while (rg - lf > 1) {
        val mid = (lf + rg) / 2
        if (count(r, c, ids, mid) < k) {
            lf = mid
        } else {
            rg = mid
        }
    }
    println(rg)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }