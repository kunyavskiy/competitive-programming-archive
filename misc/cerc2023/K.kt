fun main() {
    val (n, m) = readInts()
    val g = List(n) { mutableListOf<Int>() }
    val U = IntArray(m)
    val V = IntArray(m);
    repeat(m) {
        val (a, b) = readInts()
        U[it] = a
        V[it] = b
        g[a].add(it)
        g[b].add(it)
    }
    val parent = IntArray(n) { -1 }
    parent[0] = -2
    val cycle = DeepRecursiveFunction<Int, MutableList<Int>?> { v->
        for (id in g[v]) {
            val u = U[id] + V[id] - v
            if (parent[v] == u) continue
            if (u == 1) {
                return@DeepRecursiveFunction mutableListOf(id)
            }
            if (parent[u] != -1) continue
            parent[u] = v
            val r = callRecursive(u)
            if (r != null) {
                r.add(id)
                return@DeepRecursiveFunction r
            }
        }
        null
    }(1)
    if (cycle == null) {
        println("No solution")
        return
    }
    val cycleV = buildList<Int> {
        add(1)
        for (i in cycle) {
            add(U[i] + V[i] - last())
        }
        require(last() == 1)
        removeLast()
    }
    val cycleVSet = cycleV.toSet()
    parent.fill(-1)
    val path = DeepRecursiveFunction<Int, MutableList<Int>?> {v ->
        if (v in cycleVSet) {
            return@DeepRecursiveFunction mutableListOf()
        }
        for (id in g[v]) {
            val u = U[id] + V[id] - v
            if (parent[u] != -1) continue
            parent[u] = v
            val r = callRecursive(u)
            if (r != null) {
                r.add(id)
                return@DeepRecursiveFunction r
            }
        }
        null
    }(0)
    if (path == null) {
        println("No solution")
        return
    }
    path.reverse()
    val pathV = buildList<Int> {
        add(0)
        for (i in path) {
            add(U[i] + V[i] - last())
        }
    }
    if (pathV.last() == 1) {
        val aKeys = path + cycle[0]
        val bKeys = cycle.drop(1)
        println(aKeys.joinToString(" "))
        println(bKeys.joinToString(" "))
        for (v in pathV.drop(1)) {
            println("MOVE $v")
        }
        println("MOVE ${cycleV[1]}")
        println("DROP ${path.joinToString(" ")}")
        println("MOVE 1")
        println("DONE")
        for (v in cycleV.drop(1).reversed()) {
            println("MOVE $v")
        }
        println("GRAB")
        for (v in cycleV.drop(2)) {
            println("MOVE $v")
        }
        println("MOVE ${cycleV[0]}")
        for (v in pathV.reversed().drop(1)) {
            println("MOVE $v")
        }
        println("DONE")
        return
    }
    val index = cycleV.indexOf(pathV.last())
    require(index != -1)
    val aKeys = path + cycle.subList(0, index)
    val bKeys = cycle.subList(index, cycle.size)
    println(aKeys.joinToString(" "))
    println(bKeys.joinToString(" "))
    for (v in pathV.drop(1)) {
        println("MOVE $v")
    }
    println("DROP ${path.joinToString(" ")}")
    for (v in cycleV.subList(0, index).reversed()) {
        println("MOVE $v")
    }
    println("DONE")
    for (v in cycleV.subList(index, cycleV.size).reversed()) {
        println("MOVE $v")
    }
    println("GRAB")
    for (v in pathV.reversed().drop(1)) {
        println("MOVE $v")
    }
    println("DONE")
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }