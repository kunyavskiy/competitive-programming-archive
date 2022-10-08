import com.sun.source.tree.Tree
import java.util.TreeSet
import kotlin.random.*

private class BIT(val n: Int) {
    private val x = LongArray(n)

    fun add(pos:Int, value: Long) {
        var ppos = pos
        while (ppos < n) {
            x[ppos] += value
            ppos = ppos or (ppos + 1)
        }
    }

    fun get(pos: Int): Long {
        var ans = 0L
        var ppos = pos
        while (ppos != -1) {
            ans += x[ppos]
            ppos = (ppos and (ppos + 1)) - 1
        }
        return ans
    }
    fun get(l:Int, r:Int) = get(r - 1) - get(l - 1)
}

private fun solve() {
    readInt()
    val a = readInts().toIntArray()

    val rnds = mutableMapOf<Int, Long>()
    val rrnds = mutableMapOf<Long, Int>()
    val sets = mutableMapOf<Int, TreeSet<Int>>()

    fun conv(x:Int) = rnds.getOrPut(x) {
        Random.nextLong().also {
            rrnds[it] = x
        }
    }

    val t = BIT(a.size)
    for (i in a.indices) {
        t.add(i, conv(a[i]))
        sets.getOrPut(a[i]) { sortedSetOf() }.add(i)
    }

    fun TreeSet<Int>?.have(l:Int, r:Int) : Boolean {
        val up = this?.ceiling(l)
        if (up != null) return up < r
        return false
    }

    fun check(l: Int, r: Int) : Boolean {
        if ((r - l) % 2 == 0) return false
        val mid = (l + r) / 2
        val sr = t.get(mid, r) - t.get(l, mid)
        rrnds[sr]?.let { if (sets[it].have(mid, r)) return true }
        val sl = t.get(l, mid + 1) - t.get(mid + 1, r)
        rrnds[sl]?.let { if (sets[it].have(l, mid + 1)) return true }
        return false;
    }

    var ans = 0

    repeat(readInt()) {
        //val (ty, l, r) = readInts().let { Triple(2, it[0] - 1, it[1]) }
        val (ty, l, r) = readInts().let { Triple(it[0], it[1] - 1, it[2]) }
        when (ty) {
            1 -> {
                sets.getOrPut(a[l]) { sortedSetOf() }.remove(l)
                t.add(l, -conv(a[l]))
                a[l] = r
                t.add(l, conv(a[l]))
                sets.getOrPut(a[l]) { sortedSetOf() }.add(l)
            }
            2 -> {
                if (check(l, r)) ans += 1
            }
        }
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