private const val MOD = 1000000007
private class SegmentTree(data: List<Int>) {
    val lst = run {
        var x = 2
        while (x <= data.size) x *= 2
        x
    }
    private val tree = Array(2 * lst) { 0 to MOD - 1 }
    private val sw = BooleanArray(2 * lst)
    private fun recalc(i: Int) {
        tree[i] = maxOf(tree[2 * i].first, tree[2 * i + 1].first) to maxOf(tree[2 * i].second, tree[2 * i + 1].second)
    }

    private fun swap(v: Int) {
        sw[v] = !sw[v]
        tree[v] = tree[v].second to tree[v].first
    }

    private fun push(v: Int) {
        if (sw[v]) {
            sw[v] = false
            swap(2 * v)
            swap(2 * v + 1)
        }
    }

    init {
        for (i in data.indices) {
            tree[i + lst] = data[i] to MOD - data[i]
        }
        for (i in lst - 1 downTo 1) {
            recalc(i)
        }
    }

    fun getPos() : Int {
        var v = 1
        while (v < lst) {
            push(v)
            v = if (tree[2 * v].first == tree[v].first) {
                2 * v
            } else {
                2 * v + 1
            }
        }
        return v - lst
    }

    fun swap(v: Int, l: Int, r: Int, L: Int, R: Int) {
        if (r <= L || R <= l) return
        if (L <= l && r <= R) {
            swap(v)
            return
        }
        push(v)
        swap(2 * v, l, (l + r) / 2, L, R)
        swap(2 * v + 1, (l + r) / 2, r, L, R)
        recalc(v)
    }

    fun swap(l: Int, r: Int) {
        swap(1, 0, lst, l, r)
    }

}

private fun solve() {
    readInt()
    val a = readInts()
    val tree = SegmentTree(a)
    val res = List(readInt()) {
        val (l, r) = readInts()
        tree.swap(l - 1, r)
        tree.getPos()
    }
    println(res.sumOf { it.toLong() + 1 })
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