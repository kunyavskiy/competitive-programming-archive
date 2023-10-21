private fun solve() {
    val n = readInt()
    val p = listOf(-1) + readInts().map { it - 1 }
    val g = List(n) { mutableListOf<Int>() }
    val id = mutableMapOf<String, Int>()
    for (i in 1 until n) {
        g[p[i]].add(i)
    }
    val t = List(n) { readStrings().drop(1).map { id.getOrPut(it) { id.size } } }

    fun merge(a: MutableSet<Int>?, b: MutableSet<Int>?) : MutableSet<Int>? {
        if (a == null || b == null) return null
        //return (a + b).toMutableSet()
        val small = if (a.size < b.size) a else b
        val large = if (a.size < b.size) b else a
        large.addAll(small)
        return large
    }

    fun intersect(a: MutableSet<Int>?, b: MutableSet<Int>?) : MutableSet<Int>? {
        if (a == null) return b
        if (b == null) return a
        if (a.size < b.size) return a.filter { it in b }.toMutableSet()
        return b.filter { it in a }.toMutableSet()
    }

    val rev = id.entries.associate { it.value to it.key }

    val dfs = DeepRecursiveFunction<Int, Pair<MutableSet<Int>, MutableSet<Int>?>> { v: Int ->
        var all: MutableSet<Int>? = null
        var exceptOne: MutableSet<Int>? = null
        if (g[v].isEmpty()) {
            //println("${v + 1}: ${t[v].map { rev[it] }} | null")
            return@DeepRecursiveFunction t[v].toMutableSet() to null
        }
        for (u in g[v]) {
            val (childAll, childExceptOne) = callRecursive(u)
            if (all == null) {
                all = childAll
                exceptOne = childExceptOne
            } else {
                val newAll = intersect(all, childAll)
                val newExceptOne = merge(
                    intersect(exceptOne, childAll),
                    intersect(childExceptOne, all)
                )
                all = newAll
                exceptOne = newExceptOne
            }
        }
        require(all != null)
        //println("${v + 1}: ${all.map { rev[it] }} | ${exceptOne?.map { rev[it] }} | ${t[v].map { rev[it] }} | ${g[v].map { it + 1 }}")
        for (i in t[v]) {
            if (exceptOne == null || i in exceptOne) {
                exceptOne?.remove(i)
                all.add(i)
            }
        }
        //println("${v + 1}: ${all.map { rev[it] }} | ${exceptOne?.map { rev[it] }}")
        all to exceptOne
    }

    val ans = dfs(0)
    println(ans.first.size)
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