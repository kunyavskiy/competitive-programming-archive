import java.util.*

fun computeLst(n: Int) : Int {
    var x = 1
    while (x <= n) x *= 2
    return x
}

private class SegmentTree(n: Int) {
    private val lst = computeLst(n)
    private val tree = IntArray(2 * lst) { Int.MAX_VALUE / 2 }
    private val upd = IntArray(2 * lst)

    init {
        for (i in 0 until n) {
            tree[i + lst] = 0
        }
        for (i in lst - 1 downTo 1) {
            tree[i] = minOf(tree[2 * i], tree[2 * i + 1])
        }
    }

    private fun push(v: Int) {
        add(2 * v, upd[v])
        add(2 * v + 1, upd[v])
        upd[v] = 0
    }
    private fun add(v: Int, delta: Int) {
        upd[v] += delta
        tree[v] += delta
    }
    private fun recalc(v: Int) {
        tree[v] = minOf(tree[2 * v], tree[2 * v + 1])
    }
    private fun update(v: Int, l:Int, r:Int, L:Int, R:Int, delta: Int) {
        if (r <= L || R <= l) return
        if (L <= l && r <= R) {
            add(v, delta)
            return
        }
        push(v)
        val m = (l + r) / 2
        update(2 * v, l, m, L, R, delta)
        update(2 * v + 1, m, r, L, R, delta)
        recalc(v)
    }
    fun update(l:Int, r:Int, delta: Int) {
        //println("[$l..$r) += $delta")
        return update(1, 0, lst, l + 1, r + 1, delta)
    }
    fun getMin() = tree[1]
}

private fun solve(s: List<CharArray>, r: Int, changes: List<Pair<Int, Int>>) : List<Int> {
    val tree = SegmentTree(r + 2)
    val n = s.size
    val m = s[0].size
    val cnt = IntArray(m) { col -> (r + 1 until n).count { s[it][col] == 'X' } }
    val xs = Array(m) { col -> TreeSet((0 until n).filter { s[it][col] == 'X' })}
    val border = IntArray(m) {
            col -> (r downTo 0).filter { s[it][col] == 'X' }.getOrNull(n - r - 1 - cnt[col]) ?: -2
    }
    for (col in 0 until m) {
        tree.update(-1, border[col] + 1, 1)
        for (row in (border[col] + 1)..r) {
            if (row >= 0 && s[row][col] == 'X') {
                tree.update(row, row + 1, 1)
            }
        }
    }
    for (row in -1..r) {
        tree.update(row, row + 1, r - row)
    }
    val ans = IntArray(changes.size)
    for ((index, change) in changes.withIndex()) {
        val (x, y) = change
        if (xs[y].contains(x)) {
            xs[y].remove(x)
            if (x >= border[y]) {
                if (x <= r) {
                    tree.update(x, x + 1, -1)
                }
                val newBorder = xs[y].lower(border[y]) ?: -2
                tree.update(newBorder + 1, border[y], -1)
                border[y] = newBorder
            }
        } else {
            xs[y].add(x)
            if (x >= border[y]) {
                if (x <= r) {
                    tree.update(x, x + 1, 1)
                }
                val newBorder = if (xs[y].size >= n - r) xs[y].higher(border[y]) else -2
                tree.update(border[y] + 1, newBorder, 1)
                border[y] = newBorder
            }
        }
        ans[index] = tree.getMin()
    }
    return ans.toList()
}

private fun solve() {
    val (n, m, k, S) = readInts()
    val s = Array(n) { readLn() }
    val changes = List(S) {
        val x = readInts().map { it - 1 }
        x[0] to x[1]
    }
    val ans2 = solve(s.reversed().map {it.toCharArray()}, n - k, changes.map { n - it.first - 1 to it.second })
    val ans1 = solve(s.map { it.toCharArray() }, k - 1, changes)
    //println(ans1)
    //println(ans2)
    println(ans1.zip(ans2).map { minOf(it.first, it.second).toLong() }.sum())
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