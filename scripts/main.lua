-- State variables
local inputText = "Hello"
local checkState = false
local sliderValue = 0.3
local colorValue = { 0.8, 0.2, 0.1 }

local btnClicks = 0

function UpdateUI()
    -------------------------------
    -- Title
    -------------------------------
    ImGui.Text("ImLuaGui Demo")

    ImGui.Separator()

    -------------------------------
    -- Button Example
    -------------------------------
    ImGui.Text("Button Example:")
    if ImGui.Button("Click Me!", 120, 30) then
        btnClicks = btnClicks + 1
        print("Button clicked! Total =", btnClicks)
    end

    ImGui.Text("Click Count: " .. tostring(btnClicks))
    ImGui.Separator()

    -------------------------------
    -- InputText Example
    -------------------------------
    ImGui.Text("InputText Example:")
    local _inputText, value_changed = ImGui.InputText("Input:", inputText, 100)
    if value_changed then
        inputText = _inputText
        print("Input changed:", inputText)
    end
    ImGui.Separator()

    -------------------------------
    -- Checkbox Example
    -------------------------------
    ImGui.Text("Checkbox Example:")
    local _checkState, pressed = ImGui.Checkbox("Enable Feature", checkState)
    if pressed then
        checkState = _checkState
        print("Checkbox checkState:", checkState)
    end
    ImGui.Separator()

    -- -------------------------------
    -- -- SliderFloat Example
    -- -------------------------------
    -- ImGui.Text("SliderFloat Example:")
    -- if ImGui.SliderFloat("Value", sliderValue, 0.0, 1.0) then
    --     print("Slider:", sliderValue)
    -- end
    -- ImGui.Separator()

    -- -------------------------------
    -- -- ColorEdit3 Example
    -- -------------------------------
    -- ImGui.Text("ColorEdit3 Example:")
    -- if ImGui.ColorEdit3("Color", colorValue) then
    --     print(string.format("Color changed: %.2f %.2f %.2f",
    --         colorValue[1], colorValue[2], colorValue[3]))
    -- end

    -- ImGui.Separator()

    -------------------------------
    -- SameLine Example
    -------------------------------
    ImGui.Text("SameLine Example:")
    if ImGui.Button("Yes") then print("Yes") end
    ImGui.SameLine()
    if ImGui.Button("No") then print("No") end
end
