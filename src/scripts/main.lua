local windows = {
    createWindow(800,600,'test window'),
    createWindow(800,600,'awesome window')
}

while #windows > 0 do
    for i, w in pairs(windows) do
        print(i)
        swapBuffers(w)
        pollEvents()
        if windowShouldClose(w) then
            closeWindow(w)
            windows[i] = nil
        end
    end
end