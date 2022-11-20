import java.util.*
import kotlin.random.*
import kotlin.random.Random.Default.nextInt

private fun solve(n : Int, g: List<CharArray>) {
    val used = BooleanArray(n)
    val deg = IntArray(n) { v -> g[v].count { it == '1' }}
    fun dfs(v: Int, vs: MutableList<Int>) {
        used[v] = true
        for (u in 0 until n) {
            if (!used[u] && g[u][v] == '1') {
                dfs(u, vs)
            }
        }
        vs.add(v)
    }
    val comps = buildList {
        for (i in 0 until n) {
            if (!used[i]) {
                val x = mutableListOf<Int>()
                dfs(i, x)
                add(x.toList())
            }
        }
    }
    fun out(x: List<Int>) {
        println(x.size)
        if (x.isNotEmpty()) {
            println(x.joinToString(" ") { (it + 1).toString() })
        }
        /*for (i in x) {
            for (j in 0 until n) {
                g[i][j] = (g[i][j].code xor 1).toChar()
                g[j][i] = (g[j][i].code xor 1).toChar()
            }
        }
        Arrays.fill(used, false)
        val a = mutableListOf<Int>()
        dfs(0, a)
        require(a.size == n)*/
    }
    if (comps.size == 1) {
        System.err.println("Case 1")
        out(emptyList())
    } else {
        val nonClique = comps.firstOrNull { c -> c.any { deg[it] != c.size - 1 } }
        if (nonClique == null) {
            if (comps.size == 2 || comps.minOf { it.size } == 1) {
                System.err.println("Case 2")
                out(comps.minBy { it.size })
            } else {
                System.err.println("Case 3")
                out(listOf(comps[0][0], comps[1][0]))
            }
        } else {
            System.err.println("Case 4")
            out(listOf(nonClique.first { deg[it] != nonClique.size - 1 }))
        }
    }
}

fun main() {
    repeat(readInt()) {
        val n = readInt()
        val g = List(n) { readLn().toCharArray() }
        solve(n, g)
    }

    /*
    while (true) {
        val n = nextInt(2, 5)
        val g = List(n) { i -> CharArray(n) { nextInt(0, 1).digitToChar() } }
        for (i in 0 until n) {
            g[i][i] = '0'
            for (j in 0 until i) {
                g[i][j] = g[j][i]
            }
        }
        solve(n, g)
    }*/
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }