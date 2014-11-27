classdef LineType
    %LineType
    
    properties
        edges    = LineType.empty;
        width    = uint8.empty;
        P_width  = single.empty;
        P_dWidth = single.empty;
        P_line   = single.empty;
    end

    methods
        % LineType constructor
        function obj = LineType(stream)
            % Check input type
            obj.edges(1) = EdgeType(stream(1:18));
            obj.edges(2) = EdgeType(stream(19:36));
            obj.width    = stream(37);
            obj.P_width  = typecast(flip(stream(38:41)), 'single');
            obj.P_dWidth = typecast(flip(stream(42:45)), 'single');
            obj.P_line   = typecast(flip(stream(46:49)), 'single');
        end
        
        function stream = pack(obj)
            % pack properties into stream
            stream(1:18)  = obj.edges(1).pack();
            stream(19:36) = obj.edges(2).pack();
            stream(37)    = obj.width;
            stream(7:10)  = flip(typecast(obj.P_width, 'uint8'));
            stream(11:14) = flip(typecast(obj.P_dWidth, 'uint8'));
            stream(15:18) = flip(typecast(obj.P_line, 'uint8'));
        end
    end
end