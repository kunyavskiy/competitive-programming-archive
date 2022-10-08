import kotlin.math.*

fun up2(n: Int) : Int {
    var x = 2
    while (x < n) {
        x *= 2
    }
    return x
}
private class Tree(n: Int) {
    private val lst = up2(n)
    private val count = IntArray(2 * lst)
    private val total = LongArray(2 * lst)

    private fun setImpl(pos: Int, cf: Int) {
        var ppos = pos + lst
        count[ppos] = 1 * cf
        total[ppos] = pos * cf.toLong()
        while (ppos != 1) {
            ppos /= 2
            count[ppos] = count[ppos * 2] + count[ppos * 2 + 1]
            total[ppos] = total[ppos * 2] + total[ppos * 2 + 1]
        }
    }
    fun set(pos:Int) = setImpl(pos, 1)
    fun unset(pos:Int) = setImpl(pos, 0)

    fun getSumOfLeft(upto: Int) : Long {
        var v = 1
        var l = 0
        var r = lst
        var ans = 0L
        while (r - l > 1) {
            val mid = (l + r) / 2
            if (upto < mid) {
                v = 2 * v
                r = mid
            } else {
                ans += total[2 * v]
                v = 2 * v + 1
                l = mid
            }
        }
        return ans
    }

    fun getSumOfFirst(c_: Int) : Long {
        if (c_ == count[1]) return total[1]
        var v = 1
        var c = c_
        var ans = 0L
        while (v < lst) {
            if (count[2 * v] > c) {
                v = 2 * v
            } else {
                ans += total[2 * v]
                c -= count[2 * v]
                v = 2 * v + 1
            }
        }
        return ans
    }

    fun count() = count[1]

}

private fun solve() {
    val (n, m) = readInts()
    val t1 = Tree(n)
    val t2 = Tree(n)
    val a = readInts().toIntArray()
    for (i in 0 until n) {
        if (a[i] == 1) t1.set(i) else t2.set(i)
    }

    fun solve(z:Int) : Long {
        val c1 = t1.count();
        val c2 = t2.count()
        if (c1 % 2 != 0) return -1
        val ts = (c1 + 2 * c2) / 2 - z
        val os = z - ts
        if (ts < 0 || os < 0 || os > c1 || ts > c2) return -1
        return abs(abs(t1.getSumOfFirst(os) - t1.getSumOfLeft(z)) - abs(t2.getSumOfFirst(ts) - t2.getSumOfLeft(z)))
    }

    var ans = 0L
    repeat(m) {
        val (x, y, z) = readInts()
        if (a[x - 1] == 1) t1.unset(x - 1) else t2.unset(x - 1)
        a[x - 1] = y
        if (a[x - 1] == 1) t1.set(x - 1) else t2.set(x - 1)
        ans += solve(z)
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